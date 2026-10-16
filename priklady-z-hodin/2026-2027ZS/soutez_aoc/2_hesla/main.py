from os.path import join, dirname, realpath

def load_file(filename:str)->list:
    path = join(dirname(realpath(__file__)), filename)

    with open(path, 'r', encoding='utf-8') as f:
        return [
            (
                tuple(map(int, line.split()[0].split('-'))),
                line.split()[1][0],
                line.split()[2]
             ) 
            for line in f
            ]

def prvni_cast(passwords:list)->int:
    s=0
    for c, ch, pas in passwords:
        if c[0]<=pas.count(ch)<=c[1]:
            s+=1
    return s

def druha_cast(passwords:list)->int:
    s=0
    for c, ch, pas in passwords:
        ch1 = pas[c[0]-1]
        ch2 = pas[c[1]-1]
        if (ch1 == ch) ^ (ch2 == ch):
            s+=1
    return s
    
        

passwords = load_file("data.txt")
vysledek_1 = prvni_cast(passwords)
print(vysledek_1)
vysledek_2 = druha_cast(passwords)
print(vysledek_2)
