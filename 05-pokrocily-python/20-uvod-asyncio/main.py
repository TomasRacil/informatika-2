import asyncio
import time

async def simuluj_stahovani(soubor, doba):
    """Simuluje asynchronní I/O operaci."""
    print(f"[Start] Stahuji {soubor} ({doba}s)...")
    await asyncio.sleep(doba)  # Neuchvátí CPU, jen "čeká"
    print(f"[Hotovo] {soubor} je stažen.")
    return f"Obsah {soubor}"

async def main():
    start_time = time.perf_counter()

    print("--- Spouštím asynchronní úkoly ---")
    
    # 1. Spuštění více úkolů najednou
    # asyncio.gather naplánuje coroutiny a počká na všechny
    vysledky = await asyncio.gather(
        simuluj_stahovani("data.json", 2),
        simuluj_stahovani("obrazek.png", 1),
        simuluj_stahovani("video.mp4", 3)
    )

    end_time = time.perf_counter()
    
    print("\n--- Výsledky ---")
    for v in vysledky:
        print(f"Staženo: {v}")
    
    print(f"\nCelkový čas: {end_time - start_time:.2f} s")
    print("(Všimněte si, že celkový čas je dán nejpomalejším úkolem, nikoliv součtem!)")

if __name__ == "__main__":
    # Startovací bod pro AsyncIO
    asyncio.run(main())
