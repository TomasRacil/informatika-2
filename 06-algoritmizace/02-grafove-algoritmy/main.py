from collections import defaultdict, deque
from dataclasses import dataclass
import heapq
import math


@dataclass
class Hrana:
    """Struktura pro hranu grafu (cílový vrchol a váha)."""
    cil: int
    vaha: int = 1


class Graf:
    """Třída reprezentující graf pomocí seznamu sousednosti."""

    def __init__(self) -> None:
        self._seznam_sousedu: dict[int, list[Hrana]] = defaultdict(list)

    def pridej_hranu(self, od: int, do_vrcholu: int, vaha: int = 1) -> None:
        """Přidá orientovanou hranu (pro neorientovaný graf přidejte i obráceně)."""
        self._seznam_sousedu[od].append(Hrana(do_vrcholu, vaha))
        # Pokud by graf nebyl orientovaný, odkomentujte řádek níže:
        # self._seznam_sousedu[do_vrcholu].append(Hrana(od, vaha))

    def bfs(self, start: int) -> None:
        """Prohledávání grafu do šířky (Breadth-First Search)."""
        print(f"--- BFS (Start: {start}) ---")

        navstiveno: set[int] = {start}
        fronta: deque[int] = deque([start])

        while fronta:
            aktualni = fronta.popleft()
            print(aktualni, end=" ")

            for hrana in self._seznam_sousedu[aktualni]:
                if hrana.cil not in navstiveno:
                    navstiveno.add(hrana.cil)
                    fronta.append(hrana.cil)
        print()

    def dfs(self, start: int) -> None:
        """Prohledávání grafu do hloubky (Depth-First Search, rekurzivně)."""
        print(f"--- DFS (Start: {start}) ---")
        navstiveno: set[int] = set()
        self._dfs_rekurze(start, navstiveno)
        print()

    def _dfs_rekurze(self, vrchol: int, navstiveno: set[int]) -> None:
        navstiveno.add(vrchol)
        print(vrchol, end=" ")

        for hrana in self._seznam_sousedu[vrchol]:
            if hrana.cil not in navstiveno:
                self._dfs_rekurze(hrana.cil, navstiveno)

    def dijkstra(self, start: int, cil: int) -> None:
        """Dijkstrův algoritmus pro nalezení nejkratší cesty v ohodnoceném grafu."""
        print(f"--- Dijkstra (Z {start} do {cil}) ---")

        vzdalenosti: dict[int, float] = {vrchol: math.inf for vrchol in self._seznam_sousedu}
        for hrany in self._seznam_sousedu.values():
            for hrana in hrany:
                vzdalenosti.setdefault(hrana.cil, math.inf)
        vzdalenosti[start] = 0

        predchudci: dict[int, int] = {}
        # Prioritní fronta ukládá dvojice (vzdalenost, vrchol)
        pq: list[tuple[float, int]] = [(0, start)]

        while pq:
            aktualni_vzdalenost, aktualni_vrchol = heapq.heappop(pq)

            # Optimalizace: delší cestu k již uzavřenému vrcholu ignorujeme
            if aktualni_vzdalenost > vzdalenosti[aktualni_vrchol]:
                continue

            if aktualni_vrchol == cil:
                break

            for hrana in self._seznam_sousedu[aktualni_vrchol]:
                nova_vzdalenost = aktualni_vzdalenost + hrana.vaha
                if nova_vzdalenost < vzdalenosti[hrana.cil]:
                    vzdalenosti[hrana.cil] = nova_vzdalenost
                    predchudci[hrana.cil] = aktualni_vrchol
                    heapq.heappush(pq, (nova_vzdalenost, hrana.cil))

        if vzdalenosti.get(cil, math.inf) == math.inf:
            print("Cesta neexistuje.")
        else:
            print(f"Nejkratší vzdálenost: {int(vzdalenosti[cil])}")

            cesta: list[int] = []
            aktualni: int | None = cil
            while aktualni is not None:
                cesta.append(aktualni)
                if aktualni == start:
                    break
                aktualni = predchudci.get(aktualni)
            cesta.reverse()

            print("Cesta:", " -> ".join(map(str, cesta)))


if __name__ == "__main__":
    g = Graf()

    # Definice grafu (orientovaný, s váhami):
    #    (0) --4--> (1)
    #     |          |
    #     2          1
    #     v          v
    #    (2) --3--> (3)
    #     |        ^ |
    #     |       /  |
    #     5      1   2
    #     |     /    |
    #     v    /     v
    #    (4) -/     (5)

    g.pridej_hranu(0, 1, 4)
    g.pridej_hranu(0, 2, 2)
    g.pridej_hranu(1, 3, 1)  # Cesta 0->1->3 (délka 5)
    g.pridej_hranu(2, 3, 3)  # Cesta 0->2->3 (délka 5)
    g.pridej_hranu(2, 4, 5)
    g.pridej_hranu(4, 3, 1)  # Zkratka přes 4: 0->2->4->3 (délka 2+5+1 = 8)
    g.pridej_hranu(3, 5, 2)

    # Ukázka BFS (ignoruje váhy, bere to jako počty kroků)
    g.bfs(0)

    # Ukázka DFS
    g.dfs(0)

    # Ukázka Dijkstra (hledá nejkratší cestu podle vah)
    # Očekáváno: 0 -> 1 -> 3 -> 5 nebo 0 -> 2 -> 3 -> 5 (Vzdálenost: 7)
    g.dijkstra(0, 5)
