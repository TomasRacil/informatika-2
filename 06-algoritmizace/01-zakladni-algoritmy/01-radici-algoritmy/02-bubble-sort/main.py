def prohod(pole: list[int], i: int, j: int) -> None:
    pole[i], pole[j] = pole[j], pole[i]


def vypis_pole(pole: list[int]) -> None:
    for prvek in pole:
        print(prvek, end=" ")
    print()


def bubble_sort(pole: list[int]) -> None:
    velikost = len(pole)
    for i in range(velikost - 1):
        prohozeno = False  # Optimalizace: pokud v průchodu nic neprohodíme, je hotovo
        for j in range(0, velikost - i - 1):
            if pole[j] > pole[j + 1]:
                prohod(pole, j, j + 1)
                prohozeno = True
        if not prohozeno:
            break  # Již seřazeno


if __name__ == "__main__":
    data = [64, 34, 25, 12, 22, 11, 90]

    print("Puvodni pole: ", end="")
    vypis_pole(data)
    bubble_sort(data)
    print("Serazene pole (Bubble Sort): ", end="")
    vypis_pole(data)
