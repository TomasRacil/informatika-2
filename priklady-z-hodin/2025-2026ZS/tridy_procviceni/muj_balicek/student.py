from .chyby import KapacitaNaplnenaError, StudentJizKurzNavstevujeError

class Student:
    def __init__(self, jmeno, osobni_cislo):
        self.jmeno = jmeno
        self.osobni_cislo = osobni_cislo
        self.__znamky = {}
        self.__zapsane_kurzy = []

    def zapis_kurz(self, kurz):
        print(f"Zapisuji studenta {self.jmeno} do {kurz.kod}...", end=" ")
        
        try:
            kurz.pridej_studenta(self)
            
            self.__zapsane_kurzy.append(kurz)
            print("OK")
            
        except KapacitaNaplnenaError as e:
            print(f"CHYBA: {e}")
        except StudentJizKurzNavstevujeError as e:
            print(f"CHYBA: {e}")

    def udel_znamku(self, kurz, znamka):
        if kurz not in self.__zapsane_kurzy:
            print(f"Chyba: Student {self.jmeno} nenavštěvuje kurz {kurz.kod}, nelze udělit známku.")
            return
        if not (1 <= znamka <= 5):
            print(f"Chyba: Známka {znamka} není v intervalu 1-5.")
            return

        self.__znamky[kurz.kod] = znamka

    @property
    def studijni_prumer(self):
        if not self.__znamky:
            return 0.0
        
        hodnoty_znamek = self.__znamky.values()
        return sum(hodnoty_znamek) / len(hodnoty_znamek)
        
    def __str__(self):
        return (f"Student: {self.jmeno} ({self.osobni_cislo}), "
                f"Průměr: {self.studijni_prumer:.1f}, "
                f"Zapsáno kurzů: {len(self.__zapsane_kurzy)}")