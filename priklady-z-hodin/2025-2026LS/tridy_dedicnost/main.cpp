#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ==========================================
// 1. BÁZOVÁ TŘÍDA
// ==========================================
class Robot {
protected:
  std::string jmeno;
  int zdravi; // Energetická integrita systému

public:
  Robot(std::string jmeno, int zdravi) : jmeno(jmeno), zdravi(zdravi) {}
  virtual ~Robot() = default;

  std::string getJmeno() const { return jmeno; }
  bool jeZivy() const { return zdravi > 0; }

  // Virtuální metoda pro registraci snížení integrity (poškození)
  virtual void utrpPoskozeni(int body) {
    zdravi -= body;
    if (zdravi < 0)
      zdravi = 0;
    std::cout << "  Entita " << jmeno << " detekovala pokles integrity o "
              << body << " jednotek. (Aktualni stav: " << zdravi << ")\n";
  }

  // Čistě virtuální metoda - definuje specifický mechanismus interakce/útoku
  virtual void provedUtok(Robot &cil) = 0;
};

// ==========================================
// 2. ODVOZENÉ TŘÍDY
// ==========================================

// TODO: Implementujte třídu KamikazeRobot odvozenou z bázové třídy Robot
// (veřejná dědičnost)
// - Konstruktor deleguje parametry jmeno a zdravi konstruktoru bázové třídy.
// - Přepište virtuální metodu provedUtok(Robot& cil) s využitím klíčového slova
// override:
//   1. Vypište: "[jmeno] inicializuje destruktivni pretizeni jadra s plosnou
//   deprivaci energie!"
//   2. Aplikujte poškození 80 jednotek na cílový objekt
//   (cil.utrpPoskozeni(80)).
//   3. Aplikujte poškození 100 jednotek na instanci samotnou
//   (utrpPoskozeni(100)), což povede k její okamžité terminaci.

// TODO: Implementujte třídu LecitelRobot dědící z bázové třídy Robot
// - Deklarujte privátní členskou proměnnou (např. int silaLeceni)
// reprezentující míru regenerace integrity.
// - Konstruktor inicializuje bázovou třídu a nastaví specifický atribut pro
// regeneraci.
// - Přepište metodu provedUtok(Robot& cil) s klíčovým slovem override:
//   1. Vypište: "[jmeno] alokuje prostredky na vnitrni rekalibraci a obnovu
//   integrity."
//   2. Inkrementujte stav zdraví (integrity) o definovanou hodnotu regenerace.
//   3. Vypište aktuální úroveň integrity na standardní výstup.
//   4. Cílový objekt ponechte beze změny (objekt neprovádí vnější interakci).

// TODO: Implementujte třídu StrelnyRobot dědící z bázové třídy Robot
// - Deklarujte privátní atributy pro aktuální a maximální kapacitu aktivních
// cyklů (např. naboje, maxNaboju).
// - Konstruktor inicializuje stav bázové třídy a alokuje plnou kapacitu cyklů.
// - Přepište metodu provedUtok(Robot& cil) s klíčovým slovem override:
//   1. Jestliže je k dispozici nenulová kapacita (naboje > 0):
//      - Vypište: "[jmeno] generuje smerovany energeticky vyboj na cil
//      [cil.getJmeno()]."
//      - Redukujte integritu cílového objektu o 40 jednotek
//      (cil.utrpPoskozeni(40)).
//      - Dekrementujte počet dostupných cyklů o 1.
//   2. Jestliže je kapacita vyčerpána:
//      - Vypište: "[jmeno] nema dostatek energie pro vyboj! Spousti se
//      sekvencni dobijeni akumulatoru."
//      - Obnovte stav kapacity na maximální úroveň.
//      - Cílový objekt neovlivňujte.

int main() {
  // Inicializace simulačního registru
  std::vector<std::unique_ptr<Robot>> arena;

  /* Odkomentovat po naprogramování:
  arena.push_back(std::make_unique<KamikazeRobot>("BOOM-3000", 90));
  arena.push_back(std::make_unique<LecitelRobot>("MedBot-9", 110, 20));
  arena.push_back(std::make_unique<StrelnyRobot>("Sniper-X", 70, 2)); // 2
  cykly, poté dobíjení
  */

  if (arena.empty()) {
    std::cout << "Chyba: Nebyly inicializovany zadne subjekty v registru!"
              << std::endl;
    return 1;
  }

  std::cout << "=====================================================\n";
  std::cout << " ZAHAJENI SIMULACE DYNAMICKEHO SYSTEMU AUTONOMNICH AGENTU\n";
  std::cout << "====================================================="
            << std::endl;
  int kolo = 1;

  // Simulační smyčka běží do stabilizace stavu (aktivní maximálně 1 entita)
  while (true) {
    // Zjištění počtu aktivních entit
    int zivych = 0;
    for (const auto &r : arena) {
      if (r->jeZivy())
        zivych++;
    }

    if (zivych <= 1)
      break; // Dosaženo koncového stavu (stabilizace nebo anihilace)

    std::cout << "\n[ITERACE SIMULACE " << kolo++ << "]\n";

    // Každá aktivní entita provede interakci na další aktivní entitu v
    // definovaném pořadí
    for (size_t i = 0; i < arena.size(); ++i) {
      if (!arena[i]->jeZivy())
        continue;

      // Identifikace nejbližšího aktivního cíle v cyklickém pořadí
      Robot *cil = nullptr;
      for (size_t j = 1; j < arena.size(); ++j) {
        size_t indexCile = (i + j) % arena.size();
        if (arena[indexCile]->jeZivy()) {
          cil = arena[indexCile].get();
          break;
        }
      }

      if (cil) {
        arena[i]->provedUtok(*cil);
      }
    }
  }

  std::cout << "\n=====================================================\n";
  std::cout << " SIMULACNI CYKLUS UKONCEN \n";
  std::cout << "=====================================================\n";
  Robot *vitez = nullptr;
  for (const auto &r : arena) {
    if (r->jeZivy())
      vitez = r.get();
  }

  if (vitez) {
    std::cout << "Dominantni entita systemu: " << vitez->getJmeno() << "\n";
  } else {
    std::cout << "System ukoncen v dusledku kompletni anihilace vsech "
                 "subjektu.\n";
  }

  return 0;
}