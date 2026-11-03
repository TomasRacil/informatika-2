
from __future__ import annotations

class Cas:
    def __init__(self, hodiny:int, minuty:int):
        self.minuty = minuty
        self.hodiny = hodiny
        
    def __str__(self):
        return f"{self.hodiny}:{self.minuty}"

    def __add__(self, other:Cas)->Cas:
        minuty = self.minuty+other.minuty
        hodiny_navic = minuty//60
        minuty = minuty%60
        hodiny = self.hodiny+other.hodiny+hodiny_navic
        return Cas(hodiny, minuty)

    def __eq__(self, other):
        return (self.hodiny==other.hodiny) and (self.minuty==other.minuty)
    

cas1 = Cas(10,50)
cas2 = Cas(10,50)
print(cas1==cas2)
print(cas1+cas2)

l = [1,2,3,4,5]
len(l)
l.__len__()

