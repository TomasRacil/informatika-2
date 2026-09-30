import re
from os.path import exists, realpath, dirname, join


def read_logs(filename):
    """
    Generátor, který čte soubor řádek po řádku.
    """
    try:
        with open(join(dirname(realpath(__file__)),filename), 'r', encoding='utf-8') as f:
            for line in f:
                yield line.strip()
    except FileNotFoundError:
        print(
            f"Chyba: Soubor {filename} neexistuje. Spusť nejprve C++ program.")


class LogStat:
    def __init__(self, history_file='stats_history.txt'):
        self.history_file = join(dirname(realpath(__file__)),history_file)
        self.stats = {}
        self.load_history()

    def load_history(self):
        """
        Načte historii z jednoduchého textového souboru.
        Očekávaný formát řádku: Objekt,Level,Pocet
        """
        if exists(self.history_file):
            try:
                with open(self.history_file, 'r', encoding='utf-8') as f:
                    for line in f:
                        line = line.strip()
                        if not line:
                            continue

                        parts = line.split(',')

                        if len(parts) == 3:
                            objekt = parts[0]
                            level = parts[1]
                            pocet = int(parts[2])

                            if objekt not in self.stats:
                                self.stats[objekt] = {}
                            self.stats[objekt][level] = pocet

                print(f"Načítám historii... OK.")
            except Exception as e:
                print(f"Chyba při čtení historie: {e}")
                self.stats = {}
        else:
            print("Historie nenalezena, vytvářím novou statistiku.")

    def save_history(self):
        """
        Uloží aktuální statistiky do textového souboru.
        Formát: Objekt,Level,Pocet
        """
        try:
            with open(self.history_file, 'w', encoding='utf-8') as f:
                for objekt, urovne in self.stats.items():
                    for level, pocet in urovne.items():
                        f.write(f"{objekt},{level},{pocet}\n")
            print(f"Stav uložen do {self.history_file}")
        except Exception as e:
            print(f"Chyba při ukládání: {e}")

    def process_line(self, line):
        """Zpracuje jeden řádek pomocí Regexu"""
        pattern = r"\[(\d+)\] (\w+): (\w+) - (.*)"
        match = re.search(pattern, line)

        if match:
            level = match.group(2)
            objekt = match.group(3)

            if objekt not in self.stats:
                self.stats[objekt] = {}

            if level not in self.stats[objekt]:
                self.stats[objekt][level] = 0

            self.stats[objekt][level] += 1

    def __str__(self):
        """
        Magická metoda pro textovou reprezentaci objektu.
        Vypíše hezky formátované statistiky pro uživatele.
        """
        vystup = "\n--- Celkové Statistiky (Historie + Nyní) ---\n"
        for objekt in sorted(self.stats.keys()):
            vystup += f"{objekt}:\n"
            for level, pocet in self.stats[objekt].items():
                vystup += f"  {level:10} : {pocet}\n"
        vystup += "--------------------------------------------"
        return vystup


if __name__ == "__main__":
    statistika = LogStat()

    print("Zpracovávám server.log...")

    pocet_novych = 0
    for line in read_logs("server.log"):
        statistika.process_line(line)
        pocet_novych += 1

    print(f"Zpracováno {pocet_novych} nových záznamů.")

    print(statistika)

    statistika.save_history()
