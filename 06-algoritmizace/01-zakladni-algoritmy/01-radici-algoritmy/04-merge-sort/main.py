def vypis_pole(pole: list[int]) -> None:
    for prvek in pole:
        print(prvek, end=" ")
    print()


def merge(pole: list[int], left: int, middle: int, right: int) -> None:
    """Pomocná funkce pro slévání (merge) dvou seřazených podpolí:
    pole[left...middle] a pole[middle+1...right]
    """
    leva = pole[left : middle + 1]
    prava = pole[middle + 1 : right + 1]

    i = 0  # Index pro levé podpole
    j = 0  # Index pro pravé podpole
    k = left  # Index pro hlavní pole

    while i < len(leva) and j < len(prava):
        if leva[i] <= prava[j]:
            pole[k] = leva[i]
            i += 1
        else:
            pole[k] = prava[j]
            j += 1
        k += 1

    # Zkopírování zbývajících prvků
    while i < len(leva):
        pole[k] = leva[i]
        i += 1
        k += 1

    while j < len(prava):
        pole[k] = prava[j]
        j += 1
        k += 1


def merge_sort(pole: list[int], left: int, right: int) -> None:
    """Hlavní funkce algoritmu Merge Sort (rekurzivní)."""
    if left < right:
        middle = left + (right - left) // 2

        # 1. Rozděl: Rekurzivně seřadíme obě poloviny
        merge_sort(pole, left, middle)
        merge_sort(pole, middle + 1, right)

        # 2. Panuj: Sloučíme seřazené poloviny
        merge(pole, left, middle, right)


if __name__ == "__main__":
    data = [12, 11, 13, 5, 6, 7]

    print("Puvodni pole: ", end="")
    vypis_pole(data)
    merge_sort(data, 0, len(data) - 1)
    print("Serazene pole (Merge Sort): ", end="")
    vypis_pole(data)
