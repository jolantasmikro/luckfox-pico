#!/bin/sh

# ECM starto skriptas Luckfox RV1106
# Tikrina USB interfeisą, įkelia modulius, paleidžia DHCP ir ping testą

USB_IF="usb0"
PING_HOST="8.8.8.8"

echo "[INFO] Tikriname ECM interfeisą..."

# Įkelti modulius (jei yra)
modprobe cdc_ether 2>/dev/null
modprobe rndis_host 2>/dev/null

# Laukti, kol atsiras usb0 (max 10 sek.)
for i in $(seq 1 10); do
    if ip link show | grep -q "$USB_IF"; then
        echo "[INFO] Rasta $USB_IF"
        break
    fi
    echo "[INFO] Laukiame $USB_IF..."
    sleep 1
done

# Jei nerasta, išeiti
if ! ip link show | grep -q "$USB_IF"; then
    echo "[ERROR] $USB_IF nerasta. ECM režimas neveikia."
    exit 1
fi

# Įjungti interfeisą
ip link set $USB_IF up

# DHCP IP gavimas
echo "[INFO] Gauname IP per DHCP..."
udhcpc -i $USB_IF -q -n

# Tikriname ryšį
echo "[INFO] Tikriname ryšį su $PING_HOST..."
if ping -c 3 $PING_HOST >/dev/null 2>&1; then
    echo "[SUCCESS] Internetas veikia per ECM!"
else
    echo "[ERROR] Interneto nėra."
fi
