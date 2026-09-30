from os.path import join, realpath, dirname

numbers = ("one", "two", "three", "four", "five",
           "six", "seven", "eight", "nine")

cesta = join(dirname(realpath(__file__)), "data.txt")

suma = 0

with open(cesta, "r", encoding="utf-8") as f:
    for radek in f:
        cisla = [
            int(znak) if znak.isdigit() else
            [idx+1 
             for idx, number in enumerate(numbers)
             if radek[i:].startswith(number)][0]
            for i, znak in enumerate(radek)
            if radek.startswith(numbers, i) or znak.isdigit()]
        suma += cisla[0]*10+cisla[-1]
        print(cisla)
print(suma)
