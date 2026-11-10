import re
from os.path import realpath, dirname, join

# využíváme list comprehension pro vytvoření listu
# obsahujících jednotlivé pasy ve fromě slovníku,
# které obsahují klíče označující položky pasů a jejich hodnoty
platnePasy = [pas for pas
              in [{dvojice.split(":")[0]:dvojice.split(":")[1] for dvojice
                   in pas.split()} for pas
                  in open(join(dirname(realpath(__file__))),"data.txt", "r").read().split("\n\n")]
              if (all(k in pas for k in
                      ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"])
                  and 1920 <= int(pas['byr']) <= 2002
                  and 2010 <= int(pas['iyr']) <= 2020
                  and 2020 <= int(pas['eyr']) <= 2030
                  and ((pas['hgt'][-2:] == "cm" and
                        150 <= int(pas['hgt'][:-2]) <= 193)
                       or (pas['hgt'][-2:] == "in"
                           and 59 <= int(pas['hgt'][:-2]) <= 76))
                  and re.fullmatch(r'#[0-9a-f]{6}', pas['hcl'])
                  and pas['ecl'] in
                  ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]
                  and re.fullmatch(r"[0-9]{9}", pas['pid']))]
# 8. řádek: dělíme jednotlivé dvojice dvojtečkou a ukládáme je ve formě klíč hodnota slovníku
# 9. řádek: dělíme jednotlivé pasy pomocí split tedy mezer a newline
# 10. řádek: otevíráme soubor rozdělujeme ho na základě dvojité newline
# 11.-12. řádek: kontrolujeme jestli pas obsahuje povinné klíče
# 13. řádek: kontrolujeme jestli datum narození je ve správném rozsahu
# 14. řádek: kontrolujeme jestli datum vydání je ve správném rozsahu
# 15. řádek: kontrolujeme jestli datum expirace je ve správném rozsahu
# 16.-17. řádek: kontrolujeme jestli výška uvedená v cm je ve správném rozsahu
# 18.-19. řádek: kontrolujeme jestli výška uvedená v in je ve správném rozsahu
# 20. řádek: pomocí regulárního výrazu zjišťujeme jestli je formát barvy
# uvedený v hexadicimálně
# 21.-22. řádek: ověřujeme jestli barva očí nabývá jen určených hodnot
# 23. řádek: regulární výraz ověřuje jestli je pas id přesně devíti místné číslo

print(platnePasy)
print(len(platnePasy))