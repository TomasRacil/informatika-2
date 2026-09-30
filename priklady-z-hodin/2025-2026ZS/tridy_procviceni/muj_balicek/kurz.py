from .chyby import KapacitaNaplnenaError, StudentJizKurzNavstevujeError

class Kurz:
    def __init__(self, kod, nazev, kapacita):
        self.kod = kod
        self.nazev = nazev
        self.kapacita = kapacita
        self.__studenti = []

    def pridej_studenta(self, student):
        if len(self.__studenti) >= self.kapacita:
            raise KapacitaNaplnenaError(f"Kapacita kurzu {self.kod} je naplněna!")
        if student in self.__studenti:
            raise StudentJizKurzNavstevujeError(f"   -> Info: Student {student.jmeno} už je v kurzu zapsán.")
            # print(f"   -> Info: Student {student.jmeno} už je v kurzu zapsán.")
            # return
        self.__studenti.append(student)

    def __len__(self):
        return len(self.__studenti)

    def __str__(self):
        return f"{self.kod}: {self.nazev} [{len(self)}/{self.kapacita}]"