#!/bin/bash

echo "--- Kompilace (g++) ---"
# Přepínač -pthread a -lrt je nutný pro POSIX sdílenou paměť na Linuxu
g++ reset.cpp -o reset -lpthread -lrt
g++ racer.cpp -o racer -lpthread -lrt

if [ ! -f ./reset ] || [ ! -f ./racer ]; then
    echo "Chyba kompilace."
    exit 1
fi

echo "--- 1. Reset paměti ---"
./reset

echo "--- 2. Spouštění závodníků (Racer) ---"
# Spustíme 4 procesy na pozadí (&)
./racer &
PID1=$!
./racer &
PID2=$!
./racer &
PID3=$!
./racer &
PID4=$!

echo "Procesy spuštěny s PID: $PID1, $PID2, $PID3, $PID4"
echo "Čekám na dokončení..."

# Čekáme, až všechny procesy na pozadí skončí
wait

echo "--- HOTOVO ---"
echo "Pokud byl souběh (Race Condition), výsledná hodnota NEBUDE 400000."