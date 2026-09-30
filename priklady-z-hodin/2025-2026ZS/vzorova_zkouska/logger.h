#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
private:
    std::string nazevSouboru;
    long aktualniCas;

public:
    Logger(std::string soubor);
    void log(std::string uroven, std::string objekt, std::string zprava);
};

#endif