class HraSkoncilaError(Exception):  
    def __init__(self):
        super().__init__("Došly životy")


def nacti_cislo()->int:
    while True:
        cislo = input("Zadej cislo: ")
        try:
            cislo = int(cislo)
        except ValueError:
            print("Toto neni platne cislo")
        else: return cislo

print(nacti_cislo())