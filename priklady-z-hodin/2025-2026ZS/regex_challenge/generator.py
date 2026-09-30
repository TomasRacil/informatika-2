import random
import string
import datetime
import base64
from os.path import realpath, join, dirname

# Nastavení velikosti
NUM_LINES = 20000 
FILENAME = join(dirname(realpath(__file__)), "dump_final.txt")

# Data pro generování
DOMAINS = ["shadycorp.com", "dark.net", "phantom.org", "gmail.com", "test.loc", "protonmail.ch"]
USERS = ["neo", "admin", "root", "hacker", "cipher", "ghost", "john.doe", "alice_smith"]

def random_hex(length):
    return ''.join(random.choices("0123456789ABCDEF", k=length))

def generate_email():
    user = random.choice(USERS)
    # Modul 1: Vkládání šumu {x} do user části
    if random.random() < 0.4:
        # Rozdělíme usera a vložíme bordel
        split_idx = random.randint(1, len(user)-1)
        noise = "{" + ''.join(random.choices(string.ascii_letters + string.digits, k=random.randint(1, 3))) + "}"
        user = user[:split_idx] + noise + user[split_idx:]
    
    domain = random.choice(DOMAINS)
    return f"{user}@{domain}"

def generate_crypto():
    # Modul 2: Lookaround complexity
    tx_hash = "0x" + ''.join(random.choices("0123456789abcdef", k=random.randint(32, 64)))
    is_confirmed = random.choice([True, False])
    
    noise = ''.join(random.choices(string.ascii_letters, k=random.randint(5, 15)))
    
    line = f"TX_ID: {random.randint(1000,9999)} "
    
    if is_confirmed:
        case = random.choice(["before", "after", "far"])
        if case == "before":
            line += f"[CONFIRMED] {noise} {tx_hash}"
        elif case == "after":
            line += f"{tx_hash} {noise} [CONFIRMED]"
        else:
            # Příliš daleko na match
            line += f"[CONFIRMED] {noise*3} {tx_hash}"
    else:
        line += f"[PENDING] {noise} {tx_hash}"
        
    return line

def generate_date():
    # Modul 3: Median
    year = random.randint(2018, 2026) # 2018-2019 a 2026 jsou invalidní
    month = random.randint(1, 12)
    day = random.randint(1, 28)
    
    fmt = random.choice(["iso", "cz", "us", "text"])
    
    if fmt == "iso":
        return f"{year}-{month:02d}-{day:02d}"
    elif fmt == "cz":
        return f"{day:02d}.{month:02d}.{year}"
    elif fmt == "us":
        return f"{month:02d}/{day:02d}/{year}" # Invalid formát pro zadání
    else:
        return f"Date: {day} of {month}, {year}" # Invalid

def generate_network():
    # Modul 4: IPv6 vs MAC
    is_ipv6 = random.random() < 0.5
    
    if is_ipv6:
        # Generujeme něco co vypadá jako IPv6 a obsahuje uvnitř MAC sekvenci
        parts = [random_hex(4) for _ in range(8)]
        return f"IPv6 SRC: {':'.join(parts)}"
    else:
        # Validní MAC
        parts = [random_hex(2) for _ in range(6)]
        if random.random() < 0.2:
            parts[0] = "FF" # Invalid podle zadání
        return f"MAC DST: {':'.join(parts)}"

def generate_payload():
    # Modul 5: Base64
    has_trigger = random.random() < 0.2
    val = random.randint(1, 100)
    
    text = ''.join(random.choices(string.ascii_letters, k=10))
    if has_trigger:
        text += f" TRIGGER: {val} "
    
    encoded = base64.b64encode(text.encode()).decode()
    return f"log_dump: b64:{encoded}; end_transmission"

def generate_error():
    # Modul 6: Palindromy
    is_palindrome = random.random() < 0.1
    
    if is_palindrome:
        half = ''.join(random.choices(string.ascii_uppercase + string.digits, k=random.randint(3, 5)))
        code = half + half[::-1]
        if random.random() < 0.5: # Lichá délka
             code = half + random.choice(string.ascii_uppercase) + half[::-1]
    else:
        code = ''.join(random.choices(string.ascii_uppercase + string.digits, k=random.randint(5, 10)))
        
    return f"SysState: ERR-{code} Critical Failure"

def generate_line():
    case = random.randint(1, 7)
    timestamp = datetime.datetime.now().isoformat()
    
    if case == 1:
        return f"MSG_HEADER: {generate_email()}"
    elif case == 2:
        return f"FIN_LOG: {generate_crypto()}"
    elif case == 3:
        return f"TS_MARK: {generate_date()}"
    elif case == 4:
        return f"NET_ADAPTER: {generate_network()}"
    elif case == 5:
        return f"DATA_CHUNK: {generate_payload()}"
    elif case == 6:
        return f"SYS_KERNEL: {generate_error()}"
    else:
        return f"NOISE: {timestamp} {random_hex(20)}"

print(f"Generuji {NUM_LINES} řádků do {FILENAME}...")

with open(FILENAME, "w", encoding="utf-8") as f:
    # --- VLOŽENÍ KONTROLNÍCH DAT (EASTER EGGS) ---
    # Tato data garantují, že existuje řešení nezávislé na náhodě
    
    # M1: User s délkou 8 znaků (po očištění) -> "agent007"
    f.write("FIXED_M1: user{xyz}name@valid.com\n") # username 8 znaku
    f.write("FIXED_M1: agent{0}007@secret.com\n") # agent007 = 8 znaku
    f.write("FIXED_M1: test{1}user@test.loc\n") # Ignorovat (test.loc)
    
    # M2: Hash s potvrzením (Last valid hash digit sum)
    # Hash: 0x1111111111111111 (16 jedniček) -> součet 16
    f.write("FIXED_M2: [CONFIRMED] noise 0x1111111111111111\n") 
    
    # M3: Medián
    # Vložíme 5 dat: 2020-01-01, 2021-01-01, 2022-01-01 (Medián), 2023-01-01, 2024-01-01
    f.write("FIXED_M3: 2020-01-01\n")
    f.write("FIXED_M3: 01.01.2021\n")
    f.write("FIXED_M3: 2022-01-01\n") # Očekávaný medián z těchto fixních (pokud by byly jen tyto)
    f.write("FIXED_M3: 01.01.2023\n")
    f.write("FIXED_M3: 2024-01-01\n")

    # M4: MAC vs IPv6
    # Validní MAC, která není FF
    f.write("FIXED_M4: AA:BB:CC:DD:EE:FF\n") # 3. skupina CC
    # IPv6 matoucí
    f.write("FIXED_M4: fe80::AA:BB:CC:DD:EE:FF\n") 
    
    # M5: Payload Trigger
    # "TRIGGER: 100" encoded
    encoded_trigger = base64.b64encode(b"Some text TRIGGER: 100 end").decode()
    f.write(f"FIXED_M5: b64:{encoded_trigger};\n")
    
    # M6: Palindrom
    f.write("FIXED_M6: ERR-ABCCBA\n") # Palindrom délka 6

    # Generování zbytku
    for _ in range(NUM_LINES):
        f.write(generate_line() + "\n")
        
    # --- FIXED DATA (end - nutné pro "poslední" záznamy) ---
    
    # M2: Poslední validní hash
    # 0x22... (samé dvojky, 16x) -> součet 32
    f.write("FIXED_M2_LAST: [CONFIRMED] noise 0x2222222222222222\n") 

    # M4: Poslední validní MAC
    # AA:BB:CC:DD:EE:0F -> 3. byte je CC
    f.write("FIXED_M4_LAST: MAC DST: AA:BB:CC:DD:EE:0F\n")

print("Generování dokončeno.")