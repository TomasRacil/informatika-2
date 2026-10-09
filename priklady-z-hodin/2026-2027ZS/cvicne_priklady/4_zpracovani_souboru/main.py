from os.path import join, realpath, dirname

path = join(dirname(realpath(__file__)), "pristupy.csv") # priklady-z-hodin\2026-2027ZS\cvicne_priklady\4_zpracovani_souboru\pritupy.csv

with open(path,'r', encoding='utf-8') as f:

    hlavicka = f.readline().strip().split(';')
    index_cesty = hlavicka.index("cesta")
    index_kod = hlavicka.index("kod")
    index_velikost = hlavicka.index("velikost")

    soucet_velikosti=0
    pocet_chybovych_kodu = 0
    frekvence = dict()

    for line in f:
        line = line.strip().split(';')
        soucet_velikosti +=int(line[index_velikost])
        if int(line[index_kod])>399:
            pocet_chybovych_kodu+=1
        if line[index_cesty] in frekvence:
            frekvence[line[index_cesty]]+=1
        else:
            frekvence[line[index_cesty]]=1   

    # print(soucet_velikosti)
    # print(pocet_chybovych_kodu)
    # print(frekvence)

path = join(dirname(realpath(__file__)), "output.txt")

with open(path, 'w', encoding='utf-8') as f:
    f.write(f'soucet prenesenych dat: {soucet_velikosti}\npocet chybovych kodu: {pocet_chybovych_kodu}\nvytizenost endpointu: {frekvence}')

