def analyzuj_mereni(casy:list[int], teploty:list[float], limit:float)->tuple[int,int, list[int]]:
    """Funkce spoji dvojici listu pomoci zip() a vrati celkovy pocet hodnot, pocet hodnot preshujicich teplotni limit a indexy techto hodnot.

    Args:
        casy (list[int]): list casu
        teploty (list[float]): list teplot
        limit (float): teplotni limit

    Returns:
        tuple[int,int, list[int]]: pocet vstupnich hodnot, pocet teplot presahujicich limit, indexy teplot preshujicich limit
    """
    spojene_hodnoty = zip(casy, teploty)
    prekroceni_limitu = []
    for index, hodnoty in enumerate(spojene_hodnoty):
        cas, teplota = hodnoty
        print(f"{index}: {hodnoty}")
        if teplota > limit:
            prekroceni_limitu.append(index)

    return (index+1,len(prekroceni_limitu), prekroceni_limitu)


casy = [0, 10, 20, 30, 40, 50, 30]
teploty = [72.5, 84.0, 86.2, 85.1, 80.0, 91.4]

vysledek = analyzuj_mereni(casy, teploty, limit=85.0)
print(vysledek)
# Očekávaný výstup: (6, 3, [2, 3, 5])

