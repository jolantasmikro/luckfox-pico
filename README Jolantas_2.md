# kai neranda ttys consolės, klaida message

Jeigu tavo sistemoje TTY konsolės (pvz., ttyS0) visai nėra, tai reiškia, kad getty neturi kur veikti. Tokiu atveju yra du variantai:

✅ 1. Visiškai išjungti getty
Kadangi login per konsolę nereikalingas, tiesiog ištrink arba pakomentuok eilutę iš /etc/inittab:

```# console::respawn:/sbin/getty -L console 0 vt100```

Tada paleisk:
```kill -HUP 1```
kad init perskaitytų naują konfigūraciją.

✅ 2. Jei reikia login per serial (bet nėra sukurtos TTY)

Pakeisk inittab:
užkomentuoti:
```# ttyS0::respawn:/sbin/getty -L ttyS0 115200 vt100```