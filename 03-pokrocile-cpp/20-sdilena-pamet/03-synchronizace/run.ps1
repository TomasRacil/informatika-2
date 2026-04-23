# Skript pro spuštění synchronizovaného dema na Windows

Write-Host "--- Kompilace ---" -ForegroundColor Cyan
g++ ../02-race-condition/reset.cpp -o reset.exe
g++ safe_racer.cpp -o safe_racer.exe

if (-not (Test-Path ".\reset.exe") -or -not (Test-Path ".\safe_racer.exe")) {
    Write-Error "Chyba kompilace"
    exit
}

Write-Host "--- 1. Reset paměti ---" -ForegroundColor Cyan
./reset.exe

Write-Host "--- 2. Spouštění BEZPEČNÝCH závodníků ---" -ForegroundColor Cyan
$p1 = Start-Process -FilePath ".\safe_racer.exe" -PassThru -NoNewWindow
$p2 = Start-Process -FilePath ".\safe_racer.exe" -PassThru -NoNewWindow
$p3 = Start-Process -FilePath ".\safe_racer.exe" -PassThru -NoNewWindow
$p4 = Start-Process -FilePath ".\safe_racer.exe" -PassThru -NoNewWindow

Wait-Process -Id $p1.Id, $p2.Id, $p3.Id, $p4.Id

Write-Host "--- HOTOVO ---" -ForegroundColor Green
Write-Host "Výsledek by měl být správný (400 000) díky synchronizaci."