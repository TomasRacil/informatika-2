// Příkaz ke kompilaci:
// g++ main.cpp -o main -lcurl -pthread

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <thread>
#include <mutex>
#include <regex>
#include <atomic>
#include <curl/curl.h>

const std::string START_URL = "https://www.scrapethissite.com/pages/";
const int NUM_THREADS = 4;
const int MAX_PAGES = 50;

std::queue<std::string> url_queue;
std::set<std::string> visited_urls;
std::mutex queue_mutex;
std::mutex visited_mutex;
std::atomic<int> active_threads{0};
int pages_scraped = 0;
bool done = false;

// Callback funkce pro libcurl (ukládá data do stringu)
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Funkce pro extrakci odkazů pomocí Regexu (zjednodušené)
std::vector<std::string> extract_links(const std::string& html, const std::string& base_url) {
    std::vector<std::string> links;
    std::regex href_regex("href=[\"']([^\"']+)[\"']");
    auto words_begin = std::sregex_iterator(html.begin(), html.end(), href_regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string link = match.str(1);

        if (link.find("http") == 0) {
             links.push_back(link);
        } else {
            if (base_url.back() != '/' && link.front() != '/') {
                 links.push_back(base_url + "/" + link);
            } else {
                 links.push_back(base_url + link);
            }
        }
    }
    return links;
}

void worker(int id) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Vlákno " << id << ": Nepodařilo se inicializovat cURL." << std::endl;
        return;
    }

    while (true) {
        std::string current_url;

        // --- KRITICKÁ SEKCE: Získání URL ---
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            
            if (done && url_queue.empty()) break;
            
            if (url_queue.empty()) {
                if (active_threads == 0) {
                    done = true;
                    break;
                }
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                continue;
            }

            current_url = url_queue.front();
            url_queue.pop();
            active_threads++;
        }

        // --- KRITICKÁ SEKCE: Kontrola navštívených ---
        {
            std::unique_lock<std::mutex> lock(visited_mutex);
            if (visited_urls.count(current_url)) {
                active_threads--;
                continue;
            }
            
            if (pages_scraped >= MAX_PAGES) {
                done = true;
                active_threads--;
                break;
            }
            
            visited_urls.insert(current_url);
            pages_scraped++;
            std::cout << "[Vlákno " << id << "] Stahuji: " << current_url << std::endl;
        }

        // Stažení stránky
        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_URL, current_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        CURLcode res = curl_easy_perform(curl);

        if (res == CURLE_OK) {
            std::vector<std::string> links = extract_links(readBuffer, START_URL);
            
            // Přidání nalezených odkazů do fronty
            std::unique_lock<std::mutex> lock(queue_mutex);
            int new_links_count = 0;
            for (const auto& link : links) {
                if (!done) { 
                    url_queue.push(link);
                    new_links_count++;
                }
            }
            std::cout << "[Vlákno " << id << "] Přidáno " << new_links_count << " odkazů." << std::endl;

        } else {
            std::cerr << "[Vlákno " << id << "] Chyba cURL: " << curl_easy_strerror(res) << std::endl;
        }
        active_threads--;
    }

    curl_easy_cleanup(curl);
    std::cout << "[Vlákno " << id << "] Končí." << std::endl;
}

int main() {
    // Globální inicializace cURL
    curl_global_init(CURL_GLOBAL_ALL);

    url_queue.push(START_URL);

    std::vector<std::thread> threads;
    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    std::cout << "Hotovo. Celkem navštíveno stránek: " << visited_urls.size() << std::endl;
    curl_global_cleanup();
}