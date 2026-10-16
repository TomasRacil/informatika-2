from os.path import join, dirname, realpath

def load_file(filename:str)->list:
    path = join(dirname(realpath(__file__)), filename)

    with open(path, 'r', encoding='utf-8') as f:
        return [line.strip() for line in f]

def sjezd (mapa:list, dx:int, dy:int)->int:
    x = 0
    y = 0
    s = 0
    while y < len(mapa)-dy:
        y +=dy
        x +=dx
        x = x%(len(mapa[0]))
        if mapa[y][x]=='#': 
            s+=1
    return s

def druha_cast(mapa:list)->int:
    trajectories = [(1,1),(3,1),(5,1),(7,1),(1,2)]
    s = 1
    for dx, dy in trajectories:
        s*=sjezd(mapa, dx, dy)
    return s

mapa = load_file("test.txt")
# print(mapa)
vysledek_1 = sjezd(mapa, 3, 1)
print(vysledek_1)

vysledek_2 = druha_cast(mapa)
print(vysledek_2)