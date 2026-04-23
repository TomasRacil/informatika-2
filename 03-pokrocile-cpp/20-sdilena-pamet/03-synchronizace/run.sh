#!/bin/bash

echo "--- Kompilace (g++) ---"
# Pro reset použijeme zdroják z vedlejší složky
g++ ../02-race-condition/reset.cpp -o reset -lpthread -lrt
g++ safe_racer.cpp -o safe_racer -lpthread -lrt

if [ ! -f ./reset ] || [ ! -f ./safe_racer ]; then
    echo "Chyba kompilace."
    exit 1
fi

echo "--- 1. Reset paměti ---"
./reset

echo "--- 2. Spouštění BEZPEČNÝCH závodníků (Safe Racer) ---"
# Spustíme 4 procesy na pozadí. Díky semaforu by se neměly "poprat".
./safe_racer &
./safe_racer &
./safe_racer &
./safe_racer &

echo "Čekám na dokončení..."
wait

echo "--- HOTOVO ---"
echo "Díky semaforu by měla být výsledná hodnota přesně 400000."