# **21 - Síťová komunikace v AsyncIO**

V této části se podíváme na to, jak pomocí `asyncio` vytvářet servery a klienty. Místo nízkoúrovňových socketů budeme používat moderní **Streams API**. Ukázky najdete v souborech `server.py` a `klient.py`.

## **1. Streams API**

`asyncio` poskytuje vysokoúrovňové abstrakce `StreamReader` a `StreamWriter`. Práce s nimi je podobná práci se soubory.

### **Hlavní výhody:**
- **Automatické bufferování:** Nemusíte se starat o to, zda přišel celý paket.
- **Jednoduchost:** Žádná vlákna, vše běží v jedné smyčce.
- **Škálovatelnost:** Jeden proces zvládne tisíce simultánních spojení.

## **2. TCP Server**

Vytvoření serveru je velmi přímočaré pomocí `asyncio.start_server`.

```python
async def obsluz_klienta(reader, writer):
    data = await reader.read(100)
    # Zpracování dat...
    writer.write(data)
    await writer.drain() # Vynutí odeslání dat
    writer.close()

server = await asyncio.start_server(obsluz_klienta, '127.0.0.1', 8888)
```

## **3. TCP Klient**

Klient používá `asyncio.open_connection`, které vrací dvojici (reader, writer).

```python
reader, writer = await asyncio.open_connection('127.0.0.1', 8888)
writer.write(b"Ahoj")
await writer.drain()
odpoved = await reader.read(100)
writer.close()
```

## **4. Kdy použít co?**

- **Klasické sockety (sekce 19):** Jednoduché skripty, výuka principů sítí.
- **AsyncIO Sítě (sekce 21):** Produkční aplikace, vysoký počet klientů, moderní Python projekty.

---
## **Cvičení**

### **1. Echo Server**
Napište asynchronní server, který:
- Přečte data od klienta (do 100 bajtů).
- Data okamžitě pošle zpátky (Echo).
- Uzavře spojení.

### **2. Testovací klient**
Napište asynchronního klienta, který:
- Pošle zprávu "Halo!".
- Přečte odpověď.
- Ověří, že odpověď je "Halo!".
