from os.path import dirname, join, realpath

class Lod:
    def __init__(self):
        self.north:int = 0
        self.east:int = 0
        self.direction:str = 'E'
        
    def rotate(self, direction:str, value:int):
        directions = ["N","E","S","W"]
        idx:int = directions.index(self.direction)
        dir:int = int(4-(value/90) if direction == 'L' else value/90)
        self.direction = directions[(dir+idx)%4]
        
    def move(self, direction:str, value:int):
        match direction:
            case 'N':
                self.north+=value
            case 'S':
                self.north-=value
            case 'E':
                self.east+=value
            case 'W':
                self.east-=value
            case 'F':
                self.move(self.direction, value)
                
    def navigate(self, filename:str):
        filepath = join(dirname(realpath(__file__)), filename)
        with open(filepath, 'r', encoding='utf-8') as f:
            for line in f:
                direction = line[0]
                value = int(line[1:])
                if direction in ['L','R']:
                    self.rotate(direction, value)
                else:
                    self.move(direction, value)
            
    def __repr__(self):
        return f"N: {self.north}, E: {self.east}, distance: {abs(self.north)+abs(self.east)}"
    
class Waypoint(Lod):
    def __init__(self):
        self.north = 1
        self.east = 10
    
    def rotate(self, direction, value):
        if (value == 180):
            self.east=-self.east;
            self.north=-self.north;
        elif (value == 90 and direction=='L') or (value == 270 and direction=='R'):
            temp = self.east; 
            self.east = -self.north;
            self.north = temp;
        elif (value == 270 and direction=='L') or (value == 90 and direction=='R'):
            temp = self.east
            self.east = self.north
            self.north = -temp
    
class Lod_2(Lod):
    def __init__(self):
        self.north = 0
        self.east = 0
        self.waypoint = Waypoint()
    
    def move(self, direction, value):
        if direction =='F':
            self.north+=(self.waypoint.north*value)
            self.east+=(self.waypoint.east*value)
        else:
            self.waypoint.move(direction, value)
    
    def rotate(self, direction, value):
        self.waypoint.rotate(direction,value)
    
    
if __name__ == "__main__": 
    lod = Lod()
    lod.navigate("test.txt")
    print(lod)
    
    
    lod_2 = Lod_2()
    lod_2.navigate("test.txt")
    print(lod_2)
    