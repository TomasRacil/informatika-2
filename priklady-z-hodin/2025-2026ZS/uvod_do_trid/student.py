class Student:
    def __init__(self, jmeno:str, rocnik:int, znamky:list[int]):
        self.jmeno:str = jmeno
        self.__rocnik:int = rocnik
        self.__znamky:list[int] = znamky 
        
    @property
    def rocnik(self):
        return f"{self.__rocnik}. ročník"

    @rocnik.setter
    def rocnik(self, rocnik:int):
        if 1<=rocnik<=5:
            self.__rocnik=rocnik
        else:
            raise ValueError
        
    @property
    def znamka(self):
        return self.__znamky[-1]

    @znamka.setter
    def znamka(self, znamka:int):
        if 1<=znamka<=5:
            self.__znamky.append(znamka)
        else:
            raise ValueError
    
    def pridej_znamku(self, znamka:int):
        self.__znamky.append(znamka)
    
    def prumer(self)->float:
        return sum(self.__znamky)/len(self.__znamky)