import re
import statistics
import base64
from os.path import realpath, join, dirname

def to_hex_key(val):
    """
    Pomocná funkce pro formátování výsledků.
    Převede vstup (číslo nebo řetězec) na 4místný hexadecimální kód (např. 00AB).
    """
    if isinstance(val, int):
        h = format(val, 'X')  # Převede int na Hex (velká písmena)
    else:
        h = str(val).upper()
    return h.zfill(4)[-4:]    # Doplní nulami na 4 znaky, případně ořízne na poslední 4

def emails(content: str)->int:
    """
    ÚKOL 1: Extrakce a čištění e-mailů.
    Hledáme e-maily, kde v uživatelském jméně může být balast v {} závorkách.
    """
    # Regex rozbor:
    # ([a-zA-Z0-9._]+(?:\{[a-zA-Z0-9]+\}[a-zA-Z0-9._]*)*) 
    #   -> Uživatelské jméno: povolené znaky, následované volitelnou skupinou v {} závorkách
    # @([a-zA-Z0-9.-]+\.[a-zA-Z]{2,}) 
    #   -> Doména: alfanumerické znaky, tečka a aspoň dvouznaková koncovka
    raw_emails = re.findall(r'([a-zA-Z0-9._]+(?:\{[a-zA-Z0-9]+\}[a-zA-Z0-9._]*)*)@([a-zA-Z0-9.-]+\.[a-zA-Z]{2,})', content)

    count_len_8 = 0
    unique_clean_emails = set()

    for user_part, domain in raw_emails:
        # Ignorujeme testovací lokální domény
        if "test.loc" in domain:
            continue
            
        # Odstranění obsahu ve složených závorkách (včetně závorek)
        # re.sub(vzor, náhrada, text)
        clean_user = re.sub(r'\{.*?\}', '', user_part)
        full_email = f"{clean_user}@{domain}"
        
        # Počítáme unikátní e-maily, které mají po očištění jméno dlouhé přesně 8 znaků
        if full_email not in unique_clean_emails:
            unique_clean_emails.add(full_email)
            if len(clean_user) == 8:
                count_len_8 += 1

    print(f"M1 Result (Emails len 8): {count_len_8}")
    return to_hex_key(count_len_8)

def krypto(content: str)->int:
    """
    ÚKOL 2: Hledání potvrzených transakcí.
    Hledáme hex hashe (0x...), které jsou označené jako [CONFIRMED].
    """
    lines = content.splitlines()
    last_valid_hash = ""

    for line in lines:
        # Hledáme hexadecimální řetězec o délce 16 až 64 znaků
        match = re.search(r'(0x[0-9a-fA-F]{16,64})', line)
        if match:
            tx_hash = match.group(1)
            start, end = match.span(1) # Získáme pozici hashe v řádku
            
            # Kontrola okolí (boundary check): 
            # Díváme se 20 znaků před a 20 znaků za nalezený hash.
            prefix = line[max(0, start-20):start]
            suffix = line[end:min(len(line), end+20)]
            
            if "[CONFIRMED]" in prefix or "[CONFIRMED]" in suffix:
                last_valid_hash = tx_hash

    # Výsledkem je součet všech cifer v POSLEDNÍM nalezeném potvrzeném hashi
    digit_sum = sum(int(c) for c in last_valid_hash if c.isdigit())
    print(f"M2 Result (Hash digit sum): {digit_sum}")
    
    return to_hex_key(digit_sum)

def data(content: str)->int:
    """
    ÚKOL 3: Validace a normalizace dat.
    Hledáme ISO formát (202x-MM-DD) i český formát (DD.MM.202x).
    """
    # Regex s alternací (|):
    # ISO: \b(202[0-5])-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])\b
    # CZ:  \b(0[1-9]|[12]\d|3[01])\.(0[1-9]|1[0-2])\.(202[0-5])\b
    matches = re.findall(r'\b(202[0-5])-(0[1-9]|1[0-2])-(0[1-9]|[12]\d|3[01])\b|\b(0[1-9]|[12]\d|3[01])\.(0[1-9]|1[0-2])\.(202[0-5])\b', content)

    valid_dates = []
    for m in matches:
        if m[0]: # Pokud se chytla první (ISO) skupina
            valid_dates.append(f"{m[0]}{m[1]}{m[2]}") # Format YYYYMMDD
        else: # Pokud se chytla druhá (CZ) skupina (indexy 3,4,5 jsou D, M, Y)
            valid_dates.append(f"{m[5]}{m[4]}{m[3]}") # Format YYYYMMDD

    # Seřadíme (díky YYYYMMDD formátu řadíme chronologicky jako text)
    valid_dates.sort()
    # statistics.median_high vybere prostřední hodnotu (v případě sudého počtu tu vyšší)
    median_str = statistics.median_high(valid_dates)
    
    median_val = int(median_str)
    print(f"M3 Result (Median date): {median_val}")
    return to_hex_key(median_val)

def mac_ip(content: str)->int:
    """
    ÚKOL 4: MAC adresy vs IPv6.
    MAC adresa (6 dvojic) nesmí být součástí IPv6 adresy (detekce podle dvojteček okolo).
    """
    # Lookaround technika:
    # (?<!:) -> Negative Lookbehind: "před tímto nesmí být dvojtečka"
    # (?!:)  -> Negative Lookahead: "za tímto nesmí být dvojtečka"
    # To zajistí, že MAC adresa není uprostřed delšího IPv6 řetězce.
    macs = re.findall(r'(?<!:)\b([0-9A-Fa-f]{2}(?::[0-9A-Fa-f]{2}){5})\b(?!:)', content)

    last_mac  = None
    for mac in macs:
        # Ignorujeme adresy začínající FF (často multicast/broadcast)
        if not mac.upper().startswith("FF"):
            last_mac  = mac

    # Výsledkem je 3. bajt (např. v AA:BB:CC:... je to CC)
    byte_3 = last_mac.split(":")[2]
    print(f"M4 Result (MAC 3rd byte): {byte_3}")
    return to_hex_key(byte_3)
        
def base64_task(content: str)->int:
    """
    ÚKOL 5: Skrytá Base64 data.
    Hledáme řetězce b64:TEXT;, dekódujeme je a hledáme slovo TRIGGER.
    """
    # Najde vše v b64:...; (negovaný set [^;]+ znamená "vše kromě středníku")
    payloads = re.findall(r'b64:([^;]+);', content)
    total_trigger_sum = 0

    for p in payloads:
        try:
            # Base64 dekódování a převod na text
            decoded = base64.b64decode(p).decode('utf-8', errors='ignore')
            if "TRIGGER:" in decoded:
                # Najdi číslo za slovem TRIGGER: (povoluje mezery \s*)
                num_match = re.search(r'TRIGGER:\s*(\d+)', decoded)
                if num_match:
                    total_trigger_sum += int(num_match.group(1))
        except:
            pass # Ignorujeme nevalidní base64 řetězce

    print(f"M5 Result (Trigger sum): {total_trigger_sum}")
    return to_hex_key(total_trigger_sum)

def palindroms(content: str)->int:
    """
    ÚKOL 6: Chybové kódy a palindromy.
    Hledáme kódy ERR-XXXXX, které se čtou stejně odpředu i dozadu.
    """
    # Hledáme ERR- následované aspoň 5 alfanumerickými znaky {5,}
    error_codes = re.findall(r'ERR-([a-zA-Z0-9]{5,})', content)
    # python slicing [::-1] převrátí řetězec
    palindromes = [code for code in error_codes if code == code[::-1]]

    print(f"M6 Result (Palindromes count): {len(palindromes)}")
    return to_hex_key(len(palindromes))

# SPUŠTĚNÍ: Načte dump, provede analýzu a vypíše výsledný 24-znakový klíč
with open(join(dirname(realpath(__file__)), "dump_final.txt"), "r") as f:
    content = f.read()
    
    # Spojení výsledků do formátu XXXX-XXXX-XXXX-XXXX-XXXX-XXXX
    results = [
        emails(content), krypto(content), data(content),
        mac_ip(content), base64_task(content), palindroms(content)
    ]
    print("\nFINAL KEY:")
    print("-".join(results))