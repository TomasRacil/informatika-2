import threading
import queue
import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse
import time

START_URL = "https://www.scrapethissite.com/pages/"
NUM_THREADS = 4
MAX_PAGES = 50

url_queue = queue.Queue()
visited_urls = set()
visited_lock = threading.Lock()
active_count = 0 
active_lock = threading.Lock()
pages_scraped = 0
stop_event = threading.Event()


def get_links(html, base_url):
    """Parsuje HTML a vrací seznam absolutních URL."""
    soup = BeautifulSoup(html, 'html.parser')
    links = []
    for a_tag in soup.find_all('a', href=True):
        href = a_tag['href']
        full_url = urljoin(base_url, href)
        links.append(full_url)
    return links


def worker(thread_id):
    global pages_scraped, active_count

    print(f"[Vlákno {thread_id}] Startuje...")

    while not stop_event.is_set():
        try:
            current_url = url_queue.get(timeout=3)
            
            with active_lock:
                active_count += 1
                
        except queue.Empty:
            continue

        with visited_lock:
            if current_url in visited_urls:
                with active_lock:
                    active_count -= 1
                url_queue.task_done()
                continue
            visited_urls.add(current_url)

            if pages_scraped >= MAX_PAGES:
                stop_event.set()
                with active_lock:
                    active_count -= 1
                url_queue.task_done()
                continue
            pages_scraped += 1

        print(f"[Vlákno {thread_id}] Stahuji: {current_url}")

        try:
            response = requests.get(current_url, timeout=5)
            if response.status_code == 200:
                links = get_links(response.text, current_url)

                count_new = 0
                with visited_lock:
                    for link in links:
                        if link not in visited_urls and urlparse(link).netloc == urlparse(START_URL).netloc:
                            url_queue.put(link)
                            count_new += 1

                print(
                    f"[Vlákno {thread_id}] Nalezeno {count_new} nových odkazů na {current_url}")
            else:
                print(
                    f"[Vlákno {thread_id}] Chyba {response.status_code} na {current_url}")

        except Exception as e:
            print(
                f"[Vlákno {thread_id}] Chyba při zpracování {current_url}: {e}")
        finally:
            with active_lock:
                active_count -= 1
            url_queue.task_done()


if __name__ == "__main__":
    url_queue.put(START_URL)

    threads = []
    for i in range(NUM_THREADS):
        t = threading.Thread(target=worker, args=(i,))
        t.start()
        threads.append(t)

    try:
        while any(t.is_alive() for t in threads) and not stop_event.is_set():
            time.sleep(1)
            if url_queue.empty():
                with active_lock:
                    if active_count == 0:
                        print("Fronta je prázdná a nikdo nepracuje. Ukončuji.")
                        stop_event.set()
    except KeyboardInterrupt:
        print("Ukončování...")
        stop_event.set()

    for t in threads:
        t.join()

    print(f"Hotovo. Navštíveno {len(visited_urls)} stránek.")
    for url in visited_urls:
        print(url)
