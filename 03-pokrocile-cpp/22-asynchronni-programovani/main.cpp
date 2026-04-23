#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

// --- POMOCNÉ FUNKCE ---

void vypis_hlavicku(const std::string& text) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "  " << text << std::endl;
    std::cout << "========================================" << std::endl;
}

// Funkce pro ukázku std::async
int tezky_vypocet(int id, int cas_s) {
    std::cout << "[Async Úkol " << id << "] Startuje výpočet na " << cas_s << "s..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(cas_s));
    return id * 100;
}

// Funkce pro ukázku std::promise
void producent_dat(std::promise<std::string> prislib) {
    std::cout << "[Producent] Připravuji důležitá data..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    std::string data = "Tajná zpráva z jiného vlákna";
    std::cout << "[Producent] Data hotova, zapisuji do promise." << std::endl;
    
    prislib.set_value(data); // Předání do future
}

#include <coroutine>

// --- MINIMÁLNÍ IMPLEMENTACE KORUTINY (GENERÁTOR) ---
// Poznámka: C++20 poskytuje klíčová slova, ale ne hotové typy (jako std::generator - ten bude v C++23).
// Pro výuku musíme definovat alespoň minimální "Promise" objekt.

struct Generator {
    struct promise_type {
        int current_value;
        Generator get_return_object() { return Generator{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { std::terminate(); }
        std::suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }
        void return_void() {}
    };

    std::coroutine_handle<promise_type> handle;
    Generator(std::coroutine_handle<promise_type> h) : handle(h) {}
    ~Generator() { if (handle) handle.destroy(); }

    bool next() {
        if (!handle || handle.done()) return false;
        handle.resume();
        return !handle.done();
    }
    int value() { return handle.promise().current_value; }
};

Generator rict_cisla(int do_kolika) {
    std::cout << "[Korutina] Začínám generovat čísla..." << std::endl;
    for (int i = 1; i <= do_kolika; ++i) {
        std::cout << "[Korutina] Pozastavuji se a vracím: " << i << std::endl;
        co_yield i; // Zde se korutina zastaví a vrátí řízení do main()
        std::cout << "[Korutina] Pokračuji po probuzení..." << std::endl;
    }
    std::cout << "[Korutina] Hotovo." << std::endl;
}


int main() {
    // 1. UKÁZKA STD::ASYNC (Vysokoúrovňové)
    vypis_hlavicku("1. UKÁZKA: std::async");
    
    auto start_async = std::chrono::high_resolution_clock::now();

    // Spustíme úkoly asynchronně
    std::future<int> f1 = std::async(std::launch::async, tezky_vypocet, 1, 2);
    std::future<int> f2 = std::async(std::launch::async, tezky_vypocet, 2, 1);

    std::cout << "[Main] Čekám na výsledky z std::async..." << std::endl;
    std::cout << "[Main] Výsledek 1: " << f1.get() << std::endl;
    std::cout << "[Main] Výsledek 2: " << f2.get() << std::endl;

    auto end_async = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff_async = end_async - start_async;
    std::cout << "Celkový čas std::async: " << diff_async.count() << " s (paralelní běh)" << std::endl;


    // 2. UKÁZKA STD::PROMISE / STD::FUTURE (Nízkoúrovňové)
    vypis_hlavicku("2. UKÁZKA: std::promise & std::future");

    // Vytvoříme komunikační kanál
    std::promise<std::string> muj_prislib;
    std::future<std::string> moje_ctecku = muj_prislib.get_future();

    // Spustíme vlákno a předáme mu promise (POZOR: promise se musí předávat přes std::move)
    std::thread t(producent_dat, std::move(muj_prislib));

    std::cout << "[Main] Čekám na data od producenta (blokuuji se)..." << std::endl;
    
    // .get() čeká, dokud producent nezavolá set_value()
    std::string prijata_data = moje_ctecku.get();
    
    std::cout << "[Main] ÚSPĚCH! Přijato: \"" << prijata_data << "\"" << std::endl;

    t.join(); // Nezapomenout uklidit vlákno


    // 3. OŠETŘENÍ VÝJIMEK V ASYNC KÓDU
    vypis_hlavicku("3. UKÁZKA: Výjimky a asynchronita");

    auto f_error = std::async(std::launch::async, []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        throw std::runtime_error("Něco se pokazilo v asynchronním úkolu!");
        return 0;
    });

    try {
        std::cout << "[Main] Pokouším se získat výsledek, který selže..." << std::endl;
        f_error.get(); 
    } catch (const std::exception& e) {
        std::cout << "[Main] Zachycena výjimka z jiného vlákna: " << e.what() << std::endl;
    }


    // 4. UKÁZKA C++20 KORUTIN (co_yield)
    vypis_hlavicku("4. UKÁZKA: C++20 Korutiny (co_yield)");

    std::cout << "[Main] Vytvářím korutinu, ale ještě ji nespouštím (initial_suspend)..." << std::endl;
    auto gen = rict_cisla(3);

    while (gen.next()) {
        std::cout << "[Main] Přijal jsem od korutiny hodnotu: " << gen.value() << std::endl;
        std::cout << "[Main] Teď dělám něco v hlavním vlákně..." << std::endl;
    }

    std::cout << "\n--- VŠECHNY UKÁZKY DOKONČENY ---" << std::endl;

    return 0;
}
