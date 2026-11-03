import functools
from time import sleep, perf_counter
import logging

logging.basicConfig(
        level=logging.DEBUG,
        format='%(asctime)s - %(levelname)s - %(message)s', # Formát zprávy
        encoding='utf-8'
        )


def mereni_casu(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        start = perf_counter()
        vysledek = func(*args, **kwargs)
        end = perf_counter()
        logging.debug(f"Cas zpracovani: {end-start}s")
        return vysledek
    return wrapper

def loguj_chyby(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # print(f"LOG: Volám funkci '{func.__name__}' s argumenty: {args} {kwargs}")
        try:
            vysledek = func(*args, **kwargs)
        except Exception as e: 
            logging.error(f"Nastala chyba {e}")
        else:
            logging.debug(f"Bez problemu")
            return vysledek
    return wrapper

@loguj_chyby
@mereni_casu
def cekej(cas:int):
    sleep(cas)
    10/0
    

if __name__ == "__main__":
    cekej(2)