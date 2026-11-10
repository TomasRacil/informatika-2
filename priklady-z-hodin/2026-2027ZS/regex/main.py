import re
import argparse
import sys


def uprav_tel_cislo(cislo:str):
    vzor = r"(^\d{9}$)|(^\+\d{1,3}( \d{3}){3}$)|(^(\d{3}\-){2}(\d{3})$)"
    if re.match(vzor, cislo):
        vzor_nahrada = r"[\s\-\+]"
        return re.sub(vzor_nahrada, "", cislo)
    else:
        raise ValueError("Nespravny format cisla.")
    
    
def main():
    parser = argparse.ArgumentParser(
            description="Nastroj na kontrolu platnosti telefoniho cisla"
        )
    parser.add_argument("tel_cislo", type=str, help="Telefonni číslo")
    
    args = parser.parse_args()
    
    try:
        print(uprav_tel_cislo(args.tel_cislo))
    except ValueError as e:
        print("Neplatny format telefonniho cisla")
        sys.exit(1)
        
if __name__ == "__main__":
    main()