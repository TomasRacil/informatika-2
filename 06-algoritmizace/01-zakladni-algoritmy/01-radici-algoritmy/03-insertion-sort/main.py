def vypis_pole(pole: list[int]) -> None:
    for prvek in pole:
        print(prvek, end=" ")
    print()


def insertion_sort(pole: list[int]) -> None:
    velikost = len(pole)
    # Začínáme od druhého prvku (index 1)
    for i in range(1, velikost):
        klic = pole[i]  # Prvek, který chceme zařadit
        j = i - 1

        # Posouváme prvky v seřazené části, které jsou větší než klíč,
        # doprava, abychom uvolnili místo.
        while j >= 0 and pole[j] > klic:
            pole[j + 1] = pole[j]
            j = j - 1
        # Vložíme klíč na správné volné místo
        pole[j + 1] = klic


if __name__ == "__main__":
    data = [12, 11, 13, 5, 6]

    print("Puvodni pole: ", end="")
    vypis_pole(data)
    insertion_sort(data)
    print("Serazene pole (Insertion Sort): ", end="")
    vypis_pole(data)
