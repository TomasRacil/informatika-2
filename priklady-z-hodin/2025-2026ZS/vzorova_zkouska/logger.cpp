#include "logger.h"
#include <fstream>
#include <iostream>

Logger::Logger(std::string soubor) {
    nazevSouboru = soubor;
    aktualniCas = 1000;
}

void Logger::log(std::string uroven, std::string objekt, std::string zprava) {
    std::ofstream soubor;
    soubor.open(nazevSouboru, std::ios::app);

    if (soubor.is_open()) {
        soubor << "[" << aktualniCas << "] " 
               << uroven << ": " 
               << objekt << " - " 
               << zprava << std::endl;
        
        aktualniCas++;
        
        soubor.close();
    } else {
        std::cerr << "Chyba: Nelze otevřít soubor pro zápis!" << std::endl;
    }
}