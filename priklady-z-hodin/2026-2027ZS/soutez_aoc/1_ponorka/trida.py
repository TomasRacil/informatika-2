from os.path import join, dirname, realpath

class Ponorka:
    def __init__(self):
        self.x:int = 0
        self.y:int = 0
        self.aim:int = 0
    
    def zpracuj_prikaz(self, command:tuple[str,int]):    
        direction, value = command
        if direction == "forward":
            self.x+=value
        elif direction == "up":
            self.y-=value
        elif direction == "down":
            self.y+=value
        else: pass
        
    def zpracuj_prikaz_2(self, command:tuple[str,int]):
        direction, value = command
        if direction == "forward":
            self.x+=value
            self.y+=self.aim*value
        elif direction == "up":
            self.aim-=value
        elif direction == "down":
            self.aim+=value
        else: pass
                
    def naviguj(self, navigacni_soubor:str, druha_cast:bool = False):
        path = join(dirname(realpath(__file__)), navigacni_soubor)
        with open(path, 'r', encoding='utf-8') as f:
            for line in f:
                command = (line.split()[0],int(line.split()[1]))
                if druha_cast:
                    self.zpracuj_prikaz_2(command)
                else:
                    self.zpracuj_prikaz(command)
        
    def __repr__(self):
        return f"x={self.x}, y={self.y}, vysledna vzdalenost={self.x*self.y}"


if __name__ == "__main__":
    ponorka = Ponorka()
    ponorka.naviguj("data.txt")
    print(ponorka)
    
    
    ponorka_2 = Ponorka()
    ponorka_2.naviguj("data.txt",True)
    print(ponorka_2)
    
    # ponorka.zpracuj_prikaz(("forward",10))
    # ponorka.zpracuj_prikaz(("up",10))
    # ponorka.zpracuj_prikaz(("down",8))
    
    
    
