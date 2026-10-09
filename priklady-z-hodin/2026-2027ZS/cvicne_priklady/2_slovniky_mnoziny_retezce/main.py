def analyzuj_frekvenci_slov(vstup:str, stop_slova:list[str])->tuple[dict,set]:
    list_slov = vstup.replace('.','').replace('!','').replace('?','').replace(',','').lower().split()
    frekvence = dict()
    for slovo in list_slov:
        if slovo in stop_slova:
            continue
        if slovo in frekvence:
            frekvence[slovo]+=1
        else:
            frekvence[slovo] = 1
    unikatni = set(k for k, v in frekvence.items() if v==1)
    return frekvence, unikatni



vstup = "Python je skvělý, ale skriptovací jazyk je rychlý. Python má přehlednou syntaxi."
stop_slova = {"je", "ale", "má"}

frekvence, unikatni = analyzuj_frekvenci_slov(vstup, stop_slova)
print("Frekvence:", frekvence)
print("Pouze jednou:", unikatni)

