from os.path import join, realpath, dirname

def nacti_sklad(cesta_k_souboru:str)->dict:
    with open(cesta_k_souboru, 'r', encoding='utf-8') as f:
        _ = f.readline()
        hlavicka = ["kod","nazev","pocet","cena za kus"]
        sklad = {radek.split(';')[0]:
                 {
                    k:int(v) if v.isdigit() else v.strip() 
                    for k,v 
                  in zip(hlavicka[1:],radek.split(';')[1:])} 
                 for radek in f}

    return sklad

def aktualizuj_zasoby(sklad:dict, kod:str, zmena:int)->bool:
    if kod not in sklad:
        return False
    pomocna = sklad[kod]["pocet"]+zmena
    if pomocna<0: 
        return False
    sklad[kod]["pocet"] = pomocna
    return True

def spocti_hodnotu_skladu(sklad:dict)->int:
    return sum([
        v["pocet"]*float(v["cena za kus"])
           for _,v in 
           sklad.items()])

    

path_sklad = join(dirname(realpath(__file__)), "sklad.csv")

sklad = nacti_sklad(path_sklad)

# print(aktualizuj_zasoby(sklad, 'A101', -160))
print(sklad)
print(spocti_hodnotu_skladu(sklad))

