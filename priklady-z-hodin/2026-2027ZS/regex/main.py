import re
def uprav_tel_cislo(cislo:str):
    vzor = r"(^\d{9}$)|(^\+\d{1,3}( \d{3}){3}$)|(^(\d{3}\-){2}(\d{3})$)"
    if re.match(vzor, cislo):
        vzor_nahrada = r"[\s\-\+]"
        return re.sub(vzor_nahrada, "", cislo)
    else:
        raise ValueError("Nespravny format cisla.")
    
print(uprav_tel_cislo("123456789"))
print(uprav_tel_cislo("+420 123 456 789"))
print(uprav_tel_cislo("123-456-789"))
try:
    print(uprav_tel_cislo("123-456-789a"))
except ValueError as e:
    print(e)