class BankovniUcet:
    def __init__(self, cislo_uctu: str, majitel: str, pocatecni_zustatek: float = 0.0) -> None:
        self._cislo_uctu: str = cislo_uctu
        self._majitel: str = ""
        self._zustatek: float = 0.0
        self._historie: list[tuple[str, float]] = []

        # Nastavení přes property settery s validací
        self.majitel = majitel
        self.zustatek = pocatecni_zustatek

        if pocatecni_zustatek > 0:
            self._historie.append(("Vklad", pocatecni_zustatek))

    @property
    def cislo_uctu(self) -> str:
        """Vrátí číslo účtu (pouze pro čtení)."""
        return self._cislo_uctu

    @property
    def majitel(self) -> str:
        """Vrátí jméno majitele účtu."""
        return self._majitel

    @majitel.setter
    def majitel(self, hodnota: str) -> None:
        """Nastaví jméno majitele účtu s validací neprázdného řetězce."""
        if not isinstance(hodnota, str) or not hodnota.strip():
            raise ValueError("Jméno majitele nesmí být prázdné.")
        self._majitel = hodnota.strip()

    @property
    def zustatek(self) -> float:
        """Vrátí aktuální zůstatek na účtu."""
        return self._zustatek

    @zustatek.setter
    def zustatek(self, hodnota: float) -> None:
        """Nastaví zůstatek na účtu s kontrolou nezápornosti."""
        if hodnota < 0:
            raise ValueError("Zůstatek nemůže být záporný.")
        self._zustatek = float(hodnota)

    def vloz(self, castka: float) -> bool:
        """Vloží na účet zadanou částku. Vrátí True při úspěchu, jinak False."""
        if castka > 0:
            self._zustatek += castka
            self._historie.append(("Vklad", castka))
            return True
        return False

    def vyber(self, castka: float) -> bool:
        """Vybere z účtu zadanou částku, pokud je na něm dostatek peněz."""
        if 0 < castka <= self._zustatek:
            self._zustatek -= castka
            self._historie.append(("Výběr", castka))
            return True
        return False

    def vypis_transakce(self) -> list[str]:
        """Vrátí formátovaný přehled provedených transakcí."""
        vystup: list[str] = []
        for typ_op, castka in self._historie:
            znamenko = "+" if typ_op == "Vklad" else "-"
            vystup.append(f"{typ_op}: {znamenko}{castka:.2f} Kč")
        return vystup

    def __str__(self) -> str:
        return f"Účet {self._cislo_uctu} ({self._majitel}) - Zůstatek: {self._zustatek:.2f} Kč"

    def __repr__(self) -> str:
        return f"BankovniUcet(cislo_uctu='{self._cislo_uctu}', majitel='{self._majitel}', zustatek={self._zustatek})"


class Banka:
    def __init__(self, nazev: str) -> None:
        self.nazev: str = nazev
        self._ucty: dict[str, BankovniUcet] = {}

    def zaloz_ucet(self, cislo_uctu: str, majitel: str, pocatecni_vklad: float = 0.0) -> BankovniUcet:
        """Založí nový účet v bance a vrátí jeho instanci."""
        if cislo_uctu in self._ucty:
            raise ValueError(f"Účet {cislo_uctu} již existuje.")
        novy_ucet = BankovniUcet(cislo_uctu, majitel, pocatecni_vklad)
        self._ucty[cislo_uctu] = novy_ucet
        return novy_ucet

    def ziskej_ucet(self, cislo_uctu: str) -> BankovniUcet | None:
        """Vrátí instanci účtu podle čísla, nebo None pokud účet neexistuje."""
        return self._ucty.get(cislo_uctu)

    def preved_penize(self, z_uctu: str, na_ucet: str, castka: float) -> bool:
        """Převede peníze mezi dvěma účty v bance."""
        ucet_od = self.ziskej_ucet(z_uctu)
        ucet_do = self.ziskej_ucet(na_ucet)

        if ucet_od is None or ucet_do is None or castka <= 0:
            return False

        if ucet_od.vyber(castka):
            ucet_do.vloz(castka)
            return True
        return False

    @property
    def celkovy_kapital(self) -> float:
        """Vypočítaná vlastnost: součet zůstatků na všech účtech v bance."""
        return sum(ucet.zustatek for ucet in self._ucty.values())

    def __repr__(self) -> str:
        return f"Banka(nazev='{self.nazev}', pocet_uctu={len(self._ucty)})"


if __name__ == "__main__":
    banka = Banka("Python Banka")
    ucet1 = banka.zaloz_ucet("111/0800", "Jan Novák", 1000.0)
    ucet2 = banka.zaloz_ucet("222/0800", "Eva Černá", 500.0)

    print("--- Založené účty ---")
    print(ucet1)
    print(ucet2)

    print("\n--- Operace na účtu 1 ---")
    ucet1.vloz(500.0)
    ucet1.vyber(200.0)
    print(ucet1)

    print("\n--- Převod mezi účty ---")
    uspech = banka.preved_penize("111/0800", "222/0800", 300.0)
    print(f"Převod 300 Kč: {'Úspěšný' if uspech else 'Neúspěšný'}")
    print(ucet1)
    print(ucet2)

    print(f"\nCelkový kapitál banky: {banka.celkovy_kapital:.2f} Kč")
    print("Historie účtu 1:", ucet1.vypis_transakce())
    print("Historie účtu 2:", ucet2.vypis_transakce())

    # Ukázka zachycení chyb při validaci v property setteru
    print("\n--- Test validace parametrů ---")
    try:
        ucet1.zustatek = -50
    except ValueError as e:
        print(f"Ověření zachytilo chybu: {e}")

    try:
        ucet1.majitel = "   "
    except ValueError as e:
        print(f"Ověření zachytilo chybu: {e}")
