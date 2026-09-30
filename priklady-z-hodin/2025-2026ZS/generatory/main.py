# 1. Odpočítávání
# Napište generátorovou funkci countdown(n), která vrací čísla od n do 0 (pomocí yield). Použijte ji v cyklu for.

# 2. Nekonečná řada
# Napište generátor sud_prijmy(), který vrací posloupnost 0, 2, 4, 6... do nekonečna. 
# V hlavním programu si vyžádejte prvních 5 čísel (pomocí next()) a pak skončete. (Pozor na nekonečný cyklus!)

def countdown(n:int):
    for i in range(n, 0, -1):
        yield i

def suda_cisla():
    i =0
    while True:
        yield i
        i+=2


if __name__ == "__main__":
    
    # countd = countdown(5)
    countd = (i for i in range(5, 0, -1))
    
    # print(next(countd))
    # print(next(countd))
    # print(next(countd))
    
    suda_c = suda_cisla()
    
    for i in range(5):
        print(next(suda_c))