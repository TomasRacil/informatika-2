# vyska:int = int(input("Zadej vysku stromu: "))
# kmen_vyska:int = int(input("Zadej vysku kmene: "))
# kmen_sirka:int = int(input("Zadej sirku kmene: "))
vyska:int = 6
kmen_vyska:int = 3
kmen_sirka:int = 3

for i in range(vyska):
    # radek:str = ""
    # for j in range(i+1):
    #     radek+="*"
    # print(radek)
    print(" "*(vyska-i)+"*"*(i*2+1))

for _ in range(kmen_vyska):
    print(" "*(vyska-kmen_sirka//2)+"#"*kmen_sirka)
    

koruna = '\n'.join([" "*(vyska-i)+"*"*(i*2+1) for i in range(vyska)])

print(koruna)