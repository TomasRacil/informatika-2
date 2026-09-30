from os.path import join, dirname, realpath
from functools import wraps
import logging

logging.basicConfig(  
    level=logging.INFO,  
    # filename='app.log',
    format='%(asctime)s - %(levelname)s - %(message)s'
)

class Polozka:
    def __init__(self, nazev, cena, mnozstvi=0):
        self.nazev = nazev
        self.cena = cena
        self.mnozstvi = mnozstvi

    def __str__(self) -> str:
        return f"{self.nazev}: {self.cena:.2f} Kč ({self.mnozstvi}ks)"

    def __repr__(self)-> str:
        return f"Polozka(({self.nazev!r}, {self.cena!r},{self.mnozstvi!r} )"

    def __eq__(self, other)->bool:
        if not isinstance(other, Polozka):
            logging.warning(f"Porovnani Polozka s nepodporovanym typem: {type(other)}")
            return NotImplemented
        return self.nazev == other.nazev and self.cena == other.cena

    def __add__(self, other):
        if not isinstance(other, Polozka):
            logging.warning(f"Scitani Polozka s nepodporovanym typem: {type(other)}")
            return NotImplemented
        if self == other:
            return Polozka(self.nazev, self.cena, self.mnozstvi + other.mnozstvi)
        logging.error("Nelze scitat ruzne polozky")

LOG_PATH = join(dirname(realpath(__file__)), "log.txt")

def log_operace(func):
    @wraps(func)
    def wrapper(*args, **kwargs):
        realne_args = args[1:]
        if kwargs:
            args_repr = f"{realne_args!r}, {kwargs!r}"
        else:
            args_repr = f"{realne_args!r}"

        logging.info(f"Volani operace '{func.__name__}' s argumenty: {args_repr}")
        return func(*args, **kwargs)
    return wrapper


class Sklad:
    def __init__(self):
        self.polozky={}

    def __enter__(self):
        logging.info("Oteviram kontext skladu...")
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        cesta_k_souboru = "autosave_sklad.csv"
        self.uloz_do_csv(cesta_k_souboru)
        logging.info(f"Sklad automaticky ulozen do {cesta_k_souboru}")
        return False


    def __len__(self):
        return sum(polozka.mnozstvi for polozka in self.polozky.values())

    def __getitem__(self, index):
        return self.polozky[index]

    @log_operace
    def pridej_polozku(self, polozka):
        if polozka.nazev in self.polozky:
            self.polozky[polozka.nazev] = self.polozky[polozka.nazev] + polozka
        else:
            self.polozky[polozka.nazev] = polozka

    @log_operace
    def odeber_polozku(self, polozka):
        if polozka.nazev in self.polozky:
            try:
                self.polozky[polozka.nazev] = self.polozky[polozka.nazev] - polozka
                if polozka.mnozstvi == 0:
                    logging.info(f"Polozka '{polozka.nazev}' byla zcela odebrana ze skladu.")
                    del self.polozky[polozka.nazev]
            except ValueError as e:
                logging.error(f"Chyba pri odebirani polozky '{polozka.nazev}': {e}")
        else:
            logging.warning(f"Pokus o odebrani polozky '{polozka.nazev}', ktera neni na sklade.")



    def uloz_do_csv(self, LOG_PATH):
        logging.info(f"Ukladam sklad do souboru: {LOG_PATH}")
        try:
            with open(LOG_PATH, "w", encoding="utf-8") as f:
                f.write("nazev,cena,mnozstvi\n")
                for polozka in self.polozky.values():
                    f.write(f"{polozka.nazev},{polozka.cena},{polozka.mnozstvi}\n")
            logging.info("Sklad uspesne ulozen.")
        except IOError as e:
            logging.error(f"Nepodarilo se ulozit sklad do {LOG_PATH}: {e}")

    def nacti_z_csv(self, LOG_PATH):
        logging.info(f"Nacitam sklad ze souboru: {LOG_PATH}")
        sklad = Sklad()
        try:
            with open(LOG_PATH, "r", encoding="utf-8") as f:
                next(f)
                for line in f:
                    nazev, cena, mnozstvi = line.strip().split(",")
                    polozka = Polozka(nazev, float(cena), int(mnozstvi))
                    sklad.pridej_polozku(polozka)
            logging.info("Sklad uspesne nacten.")
            return sklad
        except FileNotFoundError:
            logging.error(f"Soubor {LOG_PATH} nenalezen.")
            return None
        except Exception as e:
            logging.error(f"Chyba pri nacitani skladu z {LOG_PATH}: {e}")
            return None

def main():
    logging.info("Spoustim hlavni program.")
    # vytvoření položek
    jablka = Polozka("Jablko", 10, 50)
    dalsi_jablka = Polozka("Jablko", 10, 20)
    hrusky = Polozka("Hruška", 15, 30)

    # test sčítání položek
    soucet_jablek = jablka + dalsi_jablka
    logging.info(f"Test scitani polozek: {soucet_jablek}")

    # práce se skladem
    sklad = Sklad()
    logging.info("Pridavam polozky do skladu.")
    sklad.pridej_polozku(jablka)
    sklad.pridej_polozku(dalsi_jablka)
    sklad.pridej_polozku(hrusky)

    logging.info(f"Stav polozky Hruska: {sklad['Hruška']}")
    logging.info(f"Celkem kusu na skladu: {len(sklad)}")

    # uložení do CSV
    sklad.uloz_do_csv("sklad_data.csv")

    # načtení ze CSV
    novy_sklad = Sklad()
    novy_sklad = novy_sklad.nacti_z_csv("sklad_datav.csv")
    
    logging.info(f"Načteno {len(novy_sklad)} kusů zboží z nového skladu.")

    logging.info("Hlavni program dokoncen.")

if __name__ == "__main__":
    main()