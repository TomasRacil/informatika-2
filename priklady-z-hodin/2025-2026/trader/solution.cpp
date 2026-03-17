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
#include <deque>
#include <iomanip>
#include <atomic>
#include <termios.h>
#include <unistd.h>

// --- KONFIGURACE ---
const int NUM_TRADERS = 100;
const int INITIAL_CASH = 1000;
const int INITIAL_MARKET_STOCKS = 10000;
const int INITIAL_PRICE = 100;
const long long INITIAL_MARKET_CASH = 1000000; // Likvidita burzy

const std::vector<std::string> SYMBOLS = {"AAPL", "TSLA", "BTC"};

std::atomic<bool> g_running{true};
std::atomic<bool> g_paused{false};

struct TradeRecord {
    std::string type;
    std::string symbol;
    int price;
    int trader_id;
};

// --- BEZPEČNÁ HISTORIE (PRO FÁZE 4) ---
struct MarketHistory {
    std::mutex mtx;
    std::deque<TradeRecord> trades;
    std::map<std::string, std::deque<int>> price_histories;
    const size_t MaxHistory = 50;

    void add_trade(TradeRecord t) {
        std::lock_guard<std::mutex> lock(mtx);
        trades.push_back(t);
        if (trades.size() > 10) trades.pop_front();
    }

    void add_price(std::string symbol, int price) {
        std::lock_guard<std::mutex> lock(mtx);
        price_histories[symbol].push_back(price);
        if (price_histories[symbol].size() > MaxHistory) price_histories[symbol].pop_front();
    }
} g_history;

// --- ORDER BOOK (P2P MATCHING) ---
struct OrderBook {
    std::mutex mtx;
    std::map<std::string, std::deque<int>> offers; // map symbol -> list of trader_ids

    void post_offer(std::string symbol, int trader_id) {
        std::lock_guard<std::mutex> lock(mtx);
        // Omezení velikosti pro udržení aktuálnosti
        if (offers[symbol].size() > 20) offers[symbol].pop_front();
        offers[symbol].push_back(trader_id);
    }

    int take_offer(std::string symbol) {
        std::lock_guard<std::mutex> lock(mtx);
        if (offers[symbol].empty()) return -1;
        int seller_id = offers[symbol].front();
        offers[symbol].pop_front();
        return seller_id;
    }
} g_order_book;

// --- MARKET (BURZA) ---
struct Market {
    std::map<std::string, int> stocks;
    std::map<std::string, int> prices;
    long long market_cash = INITIAL_MARKET_CASH;
    std::mutex market_mutex;

    Market() {
        for (const auto& s : SYMBOLS) {
            stocks[s] = INITIAL_MARKET_STOCKS;
            prices[s] = INITIAL_PRICE;
            g_history.add_price(s, INITIAL_PRICE);
        }
    }
};

// --- TRADER (OBCHODNÍK) ---
struct Trader {
    int id;
    std::string strategy_name;
    double buy_dip_threshold;    // % poklesu k nákupu (napr. 0.05 pro 5%)
    double sell_profit_target;   // % zisku k prodeji (napr. 0.10 pro 10%)
    long long cash = INITIAL_CASH;
    std::map<std::string, int> portfolio;
    std::map<std::string, int> avg_buy_price; 
    std::mutex trader_mutex;

    Trader(int _id, std::string name, double dip, double profit) 
        : id(_id), strategy_name(name), buy_dip_threshold(dip), sell_profit_target(profit) {
        for (const auto& s : SYMBOLS) {
            portfolio[s] = 0;
            avg_buy_price[s] = 0;
        }
    }
};

void print_report(Market& market, std::vector<std::unique_ptr<Trader>>& traders) {
    struct ReportRow {
        int id;
        long long realized;
        long long unrealized;
        long long total;
    };
    std::vector<ReportRow> rows;

    for (auto& t : traders) {
        long long realized = t->cash - INITIAL_CASH;
        long long unrealized = 0;
        for (const auto& s : SYMBOLS) {
            unrealized += (long long)t->portfolio[s] * market.prices[s];
        }
        rows.push_back({t->id, realized, unrealized, realized + unrealized});
    }

    // Seřazení podle celkového zisku (Total) sestupně
    std::sort(rows.begin(), rows.end(), [](const ReportRow& a, const ReportRow& b) {
        return a.total > b.total;
    });

    std::cout << "\n--- ŽEBŘÍČEK OBCHODNÍKŮ ---" << std::endl;
    std::cout << std::left << std::setw(10) << "Trader" << std::setw(15) << "Strategie" << std::setw(15) << "Realizovaný" << std::setw(12) << "Nerealiz." << std::setw(12) << "Celkem" << std::endl;
    std::cout << std::string(75, '-') << std::endl;
    
    for (const auto& row : rows) {
        std::string strat = traders[row.id]->strategy_name;
        std::cout << "TR#" << std::left << std::setw(7) << row.id 
                  << std::setw(15) << strat
                  << std::setw(15) << row.realized 
                  << std::setw(12) << row.unrealized 
                  << std::setw(12) << row.total
                  << (row.total > 0 ? "[ZISK]" : "[ZTRÁTA]") << std::endl;
    }
}

// --- TERMINAL UTILS ---
void set_terminal_raw_mode(bool enable) {
    static struct termios oldt, newt;
    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        newt.c_cc[VMIN] = 0;   // Neblokovat na read
        newt.c_cc[VTIME] = 0;  // Okamžitý návrat
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

// --- LOGIKA OBCHODOVÁNÍ (FÁZE 1 & 2) ---
void buy_from_market(Trader& trader, Market& market, std::string symbol) {
    std::lock_guard<std::mutex> m_lock(market.market_mutex);
    std::lock_guard<std::mutex> t_lock(trader.trader_mutex);
    
    int price = market.prices[symbol];
    
    if (trader.cash >= price && market.stocks[symbol] > 0) {
        trader.cash -= price;
        market.market_cash += price;
        market.stocks[symbol]--;
        
        int total_count = trader.portfolio[symbol];
        if (total_count == 0) trader.avg_buy_price[symbol] = price;
        else trader.avg_buy_price[symbol] = (trader.avg_buy_price[symbol] * total_count + price) / (total_count + 1);
        
        trader.portfolio[symbol]++;
        market.prices[symbol] += (rand() % 2); 
        g_history.add_price(symbol, market.prices[symbol]);
        g_history.add_trade({"BUY", symbol, price, trader.id});
    }
}

void sell_to_market(Trader& trader, Market& market, std::string symbol) {
    std::lock_guard<std::mutex> m_lock(market.market_mutex);
    std::lock_guard<std::mutex> t_lock(trader.trader_mutex);
    
    int price = market.prices[symbol];
    
    if (trader.portfolio[symbol] > 0 && market.market_cash >= price) {
        trader.cash += price;
        market.market_cash -= price;
        trader.portfolio[symbol]--;
        market.stocks[symbol]++;
        market.prices[symbol] = std::max(1, market.prices[symbol] - (rand() % 2));
        g_history.add_price(symbol, market.prices[symbol]);
        g_history.add_trade({"SELL", symbol, price, trader.id});
    }
}

// --- LOGIKA P2P PŘEVODU (FÁZE 3) ---
void trade_p2p(Trader& buyer, Trader& seller, Market& market, std::string symbol, double multiplier = 1.0) {
    int price;
    {
        std::lock_guard<std::mutex> lock(market.market_mutex);
        price = static_cast<int>(market.prices[symbol] * multiplier);
    }
    
    std::scoped_lock lock(buyer.trader_mutex, seller.trader_mutex);

    if (buyer.cash >= price && seller.portfolio[symbol] > 0) {
        buyer.cash -= price;
        seller.cash += price;
        seller.portfolio[symbol]--;
        buyer.portfolio[symbol]++;
        g_history.add_trade({"P2P", symbol, price, buyer.id});
    }
}

// --- MONITOROVÁNÍ A SPRÁVA BURZY (FÁZE 4 - DASHBOARD) ---
void monitor_routine(Market& market, std::vector<std::unique_ptr<Trader>>& traders) {
    std::mt19937 gen(time(0));
    // Průměr 0, směrodatná odchylka 1.5 (většina změn bude -2 až +2, ale vzácně i mnohem víc)
    std::normal_distribution<double> dist(0.0, 1.5);

    while (g_running) {
        if (g_paused) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        // ANSI Home (\033[H) přesune kurzor na začátek
        // \033[J smaže vše od kurzoru dolů (použijeme jen jednou při překreslení grafů)
        std::cout << "\033[H" << std::flush;
        {
            std::lock_guard<std::mutex> lock(g_history.mtx);
            std::cout << "============================================" << "\033[K" << std::endl;
            std::cout << "     WALL STREET SIMULATOR - LIVE FEED      " << "\033[K" << std::endl;
            std::cout << " (Stiskněte 'p' pro PAUZU/REPORT, 'q' pro KONEC) " << "\033[K" << std::endl;
            std::cout << "============================================" << "\033[K" << std::endl;
            
            for (const auto& symbol : SYMBOLS) {
                const auto& history = g_history.price_histories[symbol];
                if (history.empty()) continue;

                int min_p = 999999, max_p = 0;
                for(int p : history) {
                    if(p < min_p) min_p = p;
                    if(p > max_p) max_p = p;
                }
                if(max_p == min_p) max_p++;

                std::cout << "\nGraf " << symbol << " (Cena: $" << history.back() << "):" << "\033[K" << std::endl;
                for(int y = 3; y >= 0; --y) {
                    int threshold = min_p + (max_p - min_p) * y / 3;
                    std::cout << std::setw(3) << threshold << " | ";
                    for(int p : history) {
                        if(p >= threshold) std::cout << "#";
                        else std::cout << " ";
                    }
                    std::cout << "\033[K" << std::endl;
                }
            }
            std::cout << "\nPoslední obchody:" << "\033[K" << std::endl;
            int count = 0;
            for(auto it = g_history.trades.rbegin(); it != g_history.trades.rend() && count < 8; ++it, ++count) {
                std::cout << " [" << it->type << "] " << std::left << std::setw(5) << it->symbol 
                          << " TR#" << std::setw(4) << it->trader_id 
                          << " za $" << std::setw(5) << it->price << "\033[K" << std::endl;
            }
            // Vymazání zbývajících řádek v oblasti historie, pokud jich je méně než 8
            for(; count < 8; ++count) std::cout << "\033[K" << std::endl;
        }

        // TRŽNÍ ŠUM A SPRÁVA (MARKET CLEARING)
        {
            std::lock_guard<std::mutex> lock(market.market_mutex);
            for (const auto& symbol : SYMBOLS) {
                // 1. Gaussova volatilita (Realistický šum)
                int noise = static_cast<int>(std::round(dist(gen)));
                market.prices[symbol] = std::max(1, market.prices[symbol] + noise);
                g_history.add_price(symbol, market.prices[symbol]);

                // 2. Market Clearing: Burza vykoupí akcie z OrderBooku, pokud má peníze
                int current_price = market.prices[symbol];
                if (market.market_cash >= current_price) {
                    int seller_id = g_order_book.take_offer(symbol);
                    if (seller_id != -1) {
                        // Vykoupení akcií od čekajícího prodejce
                        // Protože sell_to_market si bere vlastní lock, musíme burzu na moment pustit
                        // nebo volat přímo vnitřní logiku. Zde burzu na moment pustíme.
                        market.market_mutex.unlock();
                        sell_to_market(*traders[seller_id], market, symbol);
                        market.market_mutex.lock();
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
void input_routine(Market& market, std::vector<std::unique_ptr<Trader>>& traders) {
    set_terminal_raw_mode(true);
    while (g_running) {
        char c;
        // Non-blocking read (VMIN=0, VTIME=0 by default in most raw modes? No, let's be safe)
        if (read(STDIN_FILENO, &c, 1) > 0) {
            if (c == 'q') {
                g_running = false;
            } else if (c == 'p') {
                g_paused = !g_paused;
                if (g_paused) {
                    // Při pauze smažeme obrazovku hned
                    std::cout << "\033[2J\033[H" << std::flush;
                    print_report(market, traders);
                    std::cout << "\nPAUZA. Stiskněte 'p' pro pokračování nebo 'q' pro ukončení." << std::endl;
                } else {
                    // Při návratu smažeme jen zbytek reportu a report samotný (zajistíme čistý start feedu)
                    std::cout << "\033[2J\033[H" << std::flush;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    set_terminal_raw_mode(false);
}

// --- MAIN LOOP PRO VLÁKNA ---
void trader_routine(Trader& me, Market& market, std::vector<std::unique_ptr<Trader>>& all_traders) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, SYMBOLS.size() - 1);

    long long i = 0;
    while (g_running) {
        if (g_paused) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        std::string symbol = SYMBOLS[dis(gen)];

        // POKUS O OBCHOD
        if (!market.market_mutex.try_lock()) {
            // BURZA JE OBSAZENÁ -> ZKUSÍME P2P MATCHING (ORDER BOOK)
            
            // Zájem o nákup? Zkusíme najít prodejce v knize
            if (me.portfolio[symbol] == 0 || (me.avg_buy_price[symbol] > 0 && market.prices[symbol] < me.avg_buy_price[symbol] * (1.0 - me.buy_dip_threshold))) {
                int seller_id = g_order_book.take_offer(symbol);
                if (seller_id != -1 && seller_id != me.id) {
                    trade_p2p(me, *all_traders[seller_id], market, symbol);
                }
            } 
            // Zájem o prodej? Zapíšeme se do knihy nabídek
            else if (me.portfolio[symbol] > 0 && market.prices[symbol] > me.avg_buy_price[symbol] * (1.0 + me.sell_profit_target)) {
                g_order_book.post_offer(symbol, me.id);
            }
        } else {
            // BURZA JE VOLNÁ -> NORMÁLNÍ OBCHOD
            int current_price = market.prices[symbol];
            market.market_mutex.unlock();

            if (me.portfolio[symbol] == 0 || current_price < me.avg_buy_price[symbol] * (1.0 - me.buy_dip_threshold)) {
                buy_from_market(me, market, symbol);
            } else if (current_price > me.avg_buy_price[symbol] * (1.0 + me.sell_profit_target)) {
                sell_to_market(me, market, symbol);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        i++;
    }
}

int main() {
    std::ios::sync_with_stdio(false); // Rychlejší výpis do konzole
    srand(time(0));
    Market market;
    std::vector<std::unique_ptr<Trader>> traders;
    std::vector<std::thread> threads;

    struct Strategy {
        std::string name;
        double dip;
        double profit;
    };
    std::vector<Strategy> strategies = {
        {"Konz.", 0.10, 0.05},
        {"Opat.", 0.07, 0.08},
        {"Vyvá.", 0.05, 0.12},
        {"Odvá.", 0.03, 0.18},
        {"Agre.", 0.02, 0.25}
    };

    for (int i = 0; i < NUM_TRADERS; ++i) {
        auto& s = strategies[i % strategies.size()];
        traders.push_back(std::make_unique<Trader>(i, s.name, s.dip, s.profit));
    }

    std::system("clear"); 
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::thread input_thread(input_routine, std::ref(market), std::ref(traders));
    std::thread monitor_thread(monitor_routine, std::ref(market), std::ref(traders));

    for (auto& t : traders) {
        threads.emplace_back(trader_routine, std::ref(*t), std::ref(market), std::ref(traders));
    }

    for (auto& t : threads) t.join();
    
    g_running = false;
    if (monitor_thread.joinable()) monitor_thread.join();
    if (input_thread.joinable()) {
        input_thread.join();
    }

    std::system("clear");
    std::cout << "--- FINAL AUDIT ---" << std::endl;
    print_report(market, traders);

    long long total_cash_system = market.market_cash;
    std::map<std::string, int> total_stocks_system;
    for(auto s : SYMBOLS) total_stocks_system[s] = market.stocks[s];

    for (auto& t : traders) {
        total_cash_system += t->cash;
        for (const auto& s : SYMBOLS) total_stocks_system[s] += t->portfolio[s];
    }

    std::cout << "\n--- AUDIT ---" << std::endl;
    std::cout << "Celková hotovost: " << total_cash_system << " (Očekáváno: " << (long long)NUM_TRADERS * INITIAL_CASH + INITIAL_MARKET_CASH << ")" << std::endl;
    for (const auto& s : SYMBOLS) {
        std::cout << "Celkem " << s << ": " << total_stocks_system[s] << " (Očekáváno: " << INITIAL_MARKET_STOCKS << ")" << std::endl;
    }

    return 0;
}
