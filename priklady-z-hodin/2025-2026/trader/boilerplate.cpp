#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>
#include <algorithm>

// --- KONFIGURACE ---
const int NUM_TRADERS = 10;
const int INITIAL_CASH = 10000;
const int INITIAL_MARKET_STOCKS = 10000; 
const int INITIAL_PRICE = 100;

const std::vector<std::string> SYMBOLS = {"AAPL", "TSLA", "BTC"};

struct Trader; // Forward deklarace

// --- MARKET (BURZA) ---
struct Market {
    std::map<std::string, int> stocks; // Zásoba akcií burzy
    std::map<std::string, int> prices; // Aktuální ceny
    long long market_cash = 1000000;   // Peníze burzy (poskytovatel likvidity)

    // TODO: Zde bude potřeba Mutex pro Fázi 2
    // std::mutex market_mutex;

    Market() {
        for (const auto& s : SYMBOLS) {
            stocks[s] = INITIAL_MARKET_STOCKS;
            prices[s] = INITIAL_PRICE;
        }
    }
};

// --- TRADER (OBCHODNÍK) ---
struct Trader {
    int id;
    long long cash = INITIAL_CASH;
    std::map<std::string, int> portfolio;
    
    // TODO: Mutex pro ochranu vlastního majetku (Fáze 3)
    std::mutex trader_mutex;

    Trader(int _id) : id(_id) {
        for (const auto& s : SYMBOLS) {
            portfolio[s] = 0;
        }
    }
};

// --- LOGIKA OBCHODOVÁNÍ (FÁZE 1 & 2) ---
void buy_from_market(Trader& trader, Market& market, std::string symbol) {
    // ---------------------------------------------------------
    // ZDE CHYBÍ ZAMYKÁNÍ (CRITICAL SECTION)
    // ---------------------------------------------------------
    
    int price = market.prices[symbol];
    
    if (trader.cash >= price && market.stocks[symbol] > 0) {
        // Umělé zpomalení pro zaručení Race Condition
        std::this_thread::sleep_for(std::chrono::microseconds(10)); 

        trader.cash -= price;
        market.market_cash += price;

        market.stocks[symbol]--;
        trader.portfolio[symbol]++;

        // Cena roste s poptávkou (nákupem)
        market.prices[symbol] += (rand() % 2); 
    }
}

void sell_to_market(Trader& trader, Market& market, std::string symbol) {
    // ---------------------------------------------------------
    // ZDE CHYBÍ ZAMYKÁNÍ (CRITICAL SECTION)
    // ---------------------------------------------------------
    int price = market.prices[symbol];
    
    if (trader.portfolio[symbol] > 0 && market.market_cash >= price) {
        std::this_thread::sleep_for(std::chrono::microseconds(10)); 

        trader.cash += price;
        market.market_cash -= price;

        trader.portfolio[symbol]--;
        market.stocks[symbol]++;

        // Cena klesá s nabídkou (prodejem)
        market.prices[symbol] = std::max(1, market.prices[symbol] - (rand() % 2));
    }
}

// --- LOGIKA P2P PŘEVODU (FÁZE 3) ---
void trade_p2p(Trader& buyer, Trader& seller, Market& market, std::string symbol) {
    // TODO: Získejte aktuální cenu z marketu
    int price = 100;

    // TODO: IMPLEMENTUJTE ZAMYKÁNÍ TAK, ABY NEDOŠLO K DEADLOCKU
    // Potřebujete zamknout oba tradery. Pozor na pořadí!
    
    if (buyer.cash >= price && seller.portfolio[symbol] > 0) {
        buyer.cash -= price;
        seller.cash += price;
        
        seller.portfolio[symbol]--;
        buyer.portfolio[symbol]++;
    }
}

// --- MONITOROVÁNÍ (FÁZE 4) ---
void monitor_routine(Market& market) {
    while (true) {
        // TODO: FÁZE 4 - Implementujte bezpečné čtení dat a vizualizaci
        // Jak bezpečně získat data z běžících obchodů?
        
        // BONUS: Implementujte inteligentní strategii (Kupuj levně, prodávej draze)
        // TIP: Každý trader může mít jinou toleranci k riziku (jiné % pro nákup/prodej).
        // TIP2: Můžete použít market.market_mutex.try_lock() – pokud je burza obsazená, 
        // zkuste raději "Matching" (prodejci vystaví nabídku na nástěnku, kupující ji tam najdou).
        
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

// --- MAIN LOOP PRO VLÁKNA ---
void trader_routine(Trader& me, Market& market, std::vector<std::unique_ptr<Trader>>& all_traders) {
    while (true) {
        std::string symbol = SYMBOLS[rand() % SYMBOLS.size()];

        // Náhodná volba operace
        if (rand() % 2 == 0) {
            buy_from_market(me, market, symbol);
        } else {
            sell_to_market(me, market, symbol);
        }

        // FÁZE 3: P2P
        if (rand() % 100 == 0) {
             int other_id = rand() % NUM_TRADERS;
             if (other_id != me.id) {
                 trade_p2p(me, *all_traders[other_id], market, symbol);
             }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

int main() {
    srand(time(0));
    Market market;
    std::vector<std::unique_ptr<Trader>> traders;

    for (int i = 0; i < NUM_TRADERS; ++i) traders.push_back(std::make_unique<Trader>(i));

    std::cout << "--- BURZA OTEVRENA ---" << std::endl;

    // TODO: FÁZE 1-3 - Vytvořte a spusťte vlákna pro tradery
    // TODO: FÁZE 4 - Spusťte monitorovací vlákno

    // TODO: Počkejte na dokončení (join) všech vláken 
    // (V nekonečné smyčce to sice nenastane, ale v reálném kódu by to tu mělo být)

    std::cout << "--- BURZA UZAVRENA (AUDIT) ---" << std::endl;

    // --- AUDIT (KONTROLA) ---
    long long total_cash = market.market_cash;
    std::map<std::string, int> total_stocks;
    for (const auto& s : SYMBOLS) total_stocks[s] = market.stocks[s];

    for (auto& t : traders) {
        total_cash += t->cash;
        for (const auto& s : SYMBOLS) total_stocks[s] += t->portfolio[s];
    }

    std::cout << "Total Cash:   " << total_cash << " (Expected: " << (long long)NUM_TRADERS * INITIAL_CASH + 1000000 << ")" << std::endl;
    for (const auto& s : SYMBOLS) {
        std::cout << "Total " << s << ": " << total_stocks[s] << " (Expected: " << INITIAL_MARKET_STOCKS << ")" << std::endl;
    }

    return 0;
}
