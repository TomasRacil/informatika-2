from os.path import join, realpath, dirname

cesta = join(dirname(realpath(__file__)), "data.txt")

suma = 0

with open(cesta, "r", encoding="utf-8") as f:
    for radek in f:
        radek = radek.strip()
        nejvetsi_cislo = max(radek[:-1])
        for i,ch in enumerate(radek):
            if ch == nejvetsi_cislo:
                druhe_nejvetsi_cislo = max(radek[i+1:])
                break
            else:
                pass
        suma+=int(nejvetsi_cislo+druhe_nejvetsi_cislo)
        
print(suma)
        
