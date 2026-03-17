# Tento skript povolí UDP port 65432 ve Firewallu pro Windows
# Spusťte jako Administrátor (Right click -> Run as Administrator)

$port = 65432
$ruleName = "UDP Shooter Game Server"

Write-Host "Pridavam pravidlo do Firewallu pro port $port (UDP)..." -ForegroundColor Cyan

New-NetFirewallRule -DisplayName $ruleName `
                    -Direction Inbound `
                    -LocalPort $port `
                    -Protocol UDP `
                    -Action Allow `
                    -Profile Any

Write-Host "Hotovo! Pravidlo '$ruleName' bylo pridano." -ForegroundColor Green
Write-Host "Nyni se ostatni pocitace mohou pripojit k vasemu serveru."
Read-Host -Prompt "Stisknete Enter pro ukonceni"
