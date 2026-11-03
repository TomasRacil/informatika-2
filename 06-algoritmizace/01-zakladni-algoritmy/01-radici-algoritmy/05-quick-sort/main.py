def prohod(pole: list[int], i: int, j: int) -> None:
    pole[i], pole[j] = pole[j], pole[i]


def vypis_pole(pole: list[int]) -> None:
    for prvek in pole:
        print(prvek, end=" ")
    print()


def partition(pole: list[int], low: int, high: int) -> int:
    """Pomocná funkce pro rozdělení (partition) pole kolem pivota."""
    pivot = pole[high]  # Bereme poslední prvek jako pivota
    i = low - 1  # Index menšího prvku

    for j in range(low, high):
        if pole[j] < pivot:
            i += 1
            prohod(pole, i, j)

    # Umístíme pivota na správné místo
    prohod(pole, i + 1, high)
    return i + 1


def quick_sort(pole: list[int], low: int, high: int) -> None:
    """Hlavní funkce algoritmu Quick Sort (rekurzivní)."""
    if low < high:
        pi = partition(pole, low, high)
        quick_sort(pole, low, pi - 1)
        quick_sort(pole, pi + 1, high)


if __name__ == "__main__":
    data = [10, 7, 8, 9, 1, 5]

    print("Puvodni pole: ", end="")
    vypis_pole(data)
    quick_sort(data, 0, len(data) - 1)
    print("Serazene pole (Quick Sort): ", end="")
    vypis_pole(data)
