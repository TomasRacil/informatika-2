# Skript pro spuštění Race Condition dema na Windows
# Předpokládá nainstalovaný g++ (MinGW) nebo upravte pro cl.exe

Write-Host "--- Kompilace ---" -ForegroundColor Cyan
g++ reset.cpp -o reset.exe
g++ racer.cpp -o racer.exe

if (-not (Test-Path ".\reset.exe") -or -not (Test-Path ".\racer.exe")) {
    Write-Error "Chyba kompilace (chybí .exe soubory)"
    exit
}

Write-Host "--- 1. Reset paměti ---" -ForegroundColor Cyan
./reset.exe

Write-Host "--- 2. Spouštění závodníků ---" -ForegroundColor Cyan
# Start-Process spustí proces nezávisle (v novém okně nebo na pozadí)
$p1 = Start-Process -FilePath ".\racer.exe" -PassThru -NoNewWindow
$p2 = Start-Process -FilePath ".\racer.exe" -PassThru -NoNewWindow
$p3 = Start-Process -FilePath ".\racer.exe" -PassThru -NoNewWindow
$p4 = Start-Process -FilePath ".\racer.exe" -PassThru -NoNewWindow

# Čekání na dokončení
Wait-Process -Id $p1.Id, $p2.Id, $p3.Id, $p4.Id

Write-Host "--- HOTOVO ---" -ForegroundColor Green