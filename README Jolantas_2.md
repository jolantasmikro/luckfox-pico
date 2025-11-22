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


# Atjungiam Console nuo UART
```
./build.sh buildrootconfig
```
```
 > System configuration ────
     [ ] Run a getty (login prompt) after boot  ----
```

# samba užkomentavimas
Faile: ```/home/jok/LuckFox/ser3net/luckfox-pico/sysdrv/Makefile```
Užkomentuoti:
```
601 #	cp $(SYSDRV_DIR)/tools/board/buildroot/samba_defconfig $(SYSDRV_DIR_OUT_ROOTFS)/etc/samba/smb.conf
602 #	cp $(SYSDRV_DIR)/tools/board/buildroot/smbpasswd_defconfig $(SYSDRV_DIR_OUT_ROOTFS)/etc/samba/smbpasswd
```

# USB nustaymas į Host
```
sysdrv/source/kernel/arch/arm/boot/dts/rv1106g-luckfox-pico-pro-max_ser3net.dts
```
```
/**********USB**********/
&usbdrd_dwc3 {
	status = "okay";
	dr_mode = "host";
//	dr_mode = "peripheral";
};
```

    