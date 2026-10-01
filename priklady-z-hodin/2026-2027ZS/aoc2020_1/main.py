from os.path import join, realpath, dirname

def prvni_reseni(cisla:list[int])->tuple:
    for index,cislo in enumerate(cisla):
        for cislo2 in cisla[index+1:]:
            if cislo+cislo2 ==2020:
                return (cislo, cislo2)

path = join(dirname(realpath(__file__)), "data.txt")

# cisla = []

# with open(path, mode="r", encoding="utf-8") as f:
#     for line in f.readlines():
#         cisla.append(int(line))

with open(path, mode="r", encoding="utf-8") as f:
    cisla = [int(line) for line in f]
print(cisla)

nalezene_hodnoty = prvni_reseni(cisla)
print(nalezene_hodnoty)