def zpracuj_radek(radek:str)->int:
    cisla = [z for z in radek if z.isdigit()]
    return int(cisla[0]+cisla[-1])

radek:str = "pqr3stu8vwx"

# print(zpracuj_radek(radek))

soucet:int = 0
with open(r"priklady-z-hodin\2026-2027ZS\aoc2023_3\input.txt", 'r', encoding='utf-8') as f:
    for line in f:
        soucet+=zpracuj_radek(line)

print(soucet)
# cislo:str = radek[3]

# print(cislo.isdigit())

# prevraceny_radek = radek[::2]

# print(prevraceny_radek)

with open(r"priklady-z-hodin\2026-2027ZS\aoc2023_3\input.txt", 'r', encoding='utf-8') as f:
    cisla = [[int(znak) for znak in radek if znak.isdigit()] for radek in f]
    print(cisla)
