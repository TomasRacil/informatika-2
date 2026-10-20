class Student:
    def __init__(self, jmeno:str, znamka:int):
        self.jmeno = jmeno
        self.__znamka = znamka
        
    @property
    def znamka(self):
        return self.__znamka
    
    @znamka.setter
    def znamka(self, hodnota):
        if 0<hodnota<6:
            self.__znamka = hodnota
        else:
            print("Neplatna hodnota")
        
    def __repr__(self):
        return f"Objekt tridy Student <jmeno: {self.jmeno}, znamka: {self.__znamka}>"
    
        
st1 = Student("Jan", 3)

print(st1)

st1.znamka = 1
st1.__
print(st1.znamka)
print(st1.__znamka)

print(st1)
