from os.path import join, dirname, realpath

def load_file(filename:str)->list:
    path = join(dirname(realpath(__file__)), filename)

    with open(path, 'r', encoding='utf-8') as f:
        return [(line.split()[0],int(line.split()[1])) for line in f]

def prvni_cast(commands:list)->int:
    x = 0
    y = 0
    for command, value in commands:
        if command == "forward":
            x+=value
        elif command == "up":
            y+=value
        elif command == "down":
            y-=value
        else: pass
    return abs(x*y)

def druha_cast(commands:list)->int:
    x = 0
    y = 0
    aim = 0
    for command, value in commands:
        if command == "forward":
            x+=value
            y+=aim*value
        elif command == "up":
            aim-=value
        elif command == "down":
            aim+=value
        else: pass
    return abs(x*y)

commands = load_file("data.txt")

vysledek_1 = prvni_cast(commands)
print(vysledek_1)

vysledek_2 = druha_cast(commands)
print(vysledek_2)
