class Lod:
    def __init__(self):
        self.nort:int = 0
        self.east:int = 0
        self.direction:str = 'E'
        
    def rotate(self, direction:str, value:int):
        directions = ["N","E","S","W"]
        idx:int = directions.index(self.direction)
        dir:int = int(4-(value/90) if direction == 'L' else value/90)
        self.direction = directions[(dir+idx)%4]
        
    
    
if __name__ == "__main__":
    lod = Lod()
    
    lod.rotate("L",180)