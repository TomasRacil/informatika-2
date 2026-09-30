from os.path import join, dirname, realpath
from functools import lru_cache


def load_file(cesta: str = join(dirname(realpath(__file__)), "test.txt")) -> str:
    with open(cesta, "r", encoding="utf-8") as f:
        return f.read()


vystup = load_file().split('\n\n')
vystup[1] = {
    radek.split('->')[0].strip(): radek.split('->')[1].strip()
    for radek in vystup[1].split('\n')
}
vychozi_polymer = vystup[0]
pravidla = vystup[1]

@lru_cache(maxsize=100)
def polymerizace_recursive(polymer: str, pocet_cyklu) -> dict:
    if len(polymer) > 2:
        vysledky = [
            {k: (v-1 if 
                 (k == polymer[i+1] and i<len(polymer)-2) 
                 else v) for k, v 
             in polymerizace_recursive(polymer[i] + polymer[i+1], pocet_cyklu).items()
             } 
                    for i in range(len(polymer)-1)]
        keys = set()
        for key in vysledky:
            keys.update(key.keys())
        vysledek = {k:0 for k in keys}
        for d in vysledky:
            for k,v in d.items():
                vysledek[k]+=v
        return vysledek

    if pocet_cyklu > 0:
        rozsirujici_prvek = pravidla[polymer]
        polymer = polymer[0]+rozsirujici_prvek+polymer[1]
        vysledek_1 = polymerizace_recursive(polymer[:2], pocet_cyklu-1)
        vysledek_2 = polymerizace_recursive(polymer[1:], pocet_cyklu-1)
        vysledek = {k: vysledek_1.get(k, 0) + vysledek_2.get(k, 0)
                    for k in set(vysledek_1) | set(vysledek_2)}
        vysledek[rozsirujici_prvek] -= 1
        return vysledek

    else:
        return {c: polymer.count(c) for c in set(polymer)}


def main():
    vysledky = polymerizace_recursive(vychozi_polymer, 40)
    serazene_vysledky =sorted(vysledky.values())
    print(serazene_vysledky[-1]-serazene_vysledky[0])


if __name__ == "__main__":
    main()
