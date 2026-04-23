/* * POZOR: Tento příklad vyžaduje C++20.
 * Pokud používáte g++, musíte kompilovat s přepínačem -std=c++20
 * (Ve VS Code task.json přidejte "-std=c++20" do args)
 */

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <semaphore> // Novinka v C++20

// Semafor, který povolí maximálně 3 vlákna najednou
// (Např. máme jen 3 tiskárny nebo 3 volná místa v parkovišti)
std::counting_semaphore<3> semafor(3);

void zaparkujAuto(int id) {
    std::cout << "Auto " << id << " prijelo a ceka na misto..." << std::endl;

    // acquire() sníží čítač. Pokud je 0, vlákno se zablokuje a čeká.
    semafor.acquire(); 

    std::cout << ">>> Auto " << id << " ZAPARKOVALO." << std::endl;
    
    // Simulace stání na parkovišti
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "<<< Auto " << id << " ODJIZDI." << std::endl;

    // release() zvýší čítač a případně probudí čekající vlákno
    semafor.release();
}

int main() {
    std::vector<std::thread> auta;

    // Simulujeme příjezd 6 aut, ale místa jsou jen 3
    for (int i = 1; i <= 6; ++i) {
        auta.emplace_back(zaparkujAuto, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    for (auto& t : auta) {
        t.join();
    }

    return 0;
}