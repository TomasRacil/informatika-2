def prohod(pole: list[int], i: int, j: int) -> None:
    pole[i], pole[j] = pole[j], pole[i]


def vypis_pole(pole: list[int]) -> None:
    for prvek in pole:
        print(prvek, end=" ")
    print()


def selection_sort(pole: list[int]) -> None:
    velikost = len(pole)
    for i in range(velikost - 1):
        # Najdeme index nejmenšího prvku ve zbývající části
        min_idx = i
        for j in range(i + 1, velikost):
            if pole[j] < pole[min_idx]:
                min_idx = j
        # Prohodíme ho s prvním prvkem neseřazené části
        if min_idx != i:
            prohod(pole, min_idx, i)


if __name__ == "__main__":
    data = [64, 25, 12, 22, 11]

    print("Puvodni pole: ", end="")
    vypis_pole(data)
    selection_sort(data)
    print("Serazene pole (Selection Sort): ", end="")
    vypis_pole(data)
