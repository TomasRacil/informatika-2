import random

hadane_cislo = random.randrange(1, 9)

while True:
    tip = input("Zadej svuj tip: ")
    try:
        if int(tip) == hadane_cislo:
            print("Uhodl jsi!")
            print(int(tip)/0)
            break
        elif int(tip)> hadane_cislo:
            print("Hledane cislo je mensi.")
        elif int(tip)< hadane_cislo:
            print("Hledane cislo je vetsi.")
    except ValueError:
        print("Zadej platne cislo!")
    except ZeroDivisionError:
        print("Chyba deleni nulou?")
    except Exception as e:
        print(e)
        

