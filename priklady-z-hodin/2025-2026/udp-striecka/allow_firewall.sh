#!/bin/bash

# Tento skript povolí UDP port 65432 na Linuxu
# Podporuje UFW (Ubuntu/Mint) a firewalld (Fedora/CentOS)

PORT=65432

echo "Zjistuji firewall..."

if command -v ufw >/dev/null 2>&1; then
    echo "Nalezen UFW. Povoluji port $PORT/udp..."
    sudo ufw allow $PORT/udp
    echo "Hotovo."
elif command -v firewall-cmd >/dev/null 2>&1; then
    echo "Nalezen firewalld. Povoluji port $PORT/udp..."
    sudo firewall-cmd --zone=public --add-port=$PORT/udp --permanent
    sudo firewall-cmd --reload
    echo "Hotovo."
else
    echo "Nenalezen standardni firewall manager (ufw/firewalld)."
    echo "Zkuste rucne: sudo iptables -A INPUT -p udp --dport $PORT -j ACCEPT"
fi
