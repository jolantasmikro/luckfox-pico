![luckfox](https://github.com/LuckfoxTECH/luckfox-pico/assets/144299491/cec5c4a5-22b9-4a9a-abb1-704b11651e88)
# Luckfox Pico SDK
[DTS](./README_CN.md)
##  Edit: 
1. /home/jok/LuckFox/ser3net/luckfox-pico/sysdrv/source/kernel/arch/arm/boot/dts/rv1106g-luckfox-pico-pro-max.dts

[KERNEL]
```shell
cd /home/jok/LuckFox/ser3net/luckfox-pico/sysdrv/source/kernel
cp ./arch/arm/configs/luckfox_rv1106_linux_defconfig .config
make ARCH=arm menuconfig
```
1. Add PPP () Network device support -> ppp 
a. PPP support for async serial ports
b. PPP support for sync tty ports 

```shell
make ARCH=arm savedefconfig
cp defconfig ./arch/arm/configs/luckfox_rv1106_linux_defconfig
```

```shell
luckfox@luckfox:~/luckfox-pico$ ./build.sh lunch
luckfox@luckfox:~/Luckfox-Pico/luckfox-pico$ ./build.sh
```

[BUILDROOT]

```shell
cd /home/jok/LuckFox/ser3net/luckfox-pico/sysdrv/source/buildroot/buildroot-2023.02.6/
make luckfox_pico_defconfig
make menuconfig
```
1. Add minicom
2. Add iftop 

```shell
make savedefconfig 
make
```


[CONSOLE_From_UART2]
(https://forums.luckfox.com/viewtopic.php?t=975)

1. Nusikopijuojam 
    rv1106_ddr_924MHz_v1.10.bin iš /luckfox-pico/sysdrv/source/uboot/rkbin/bin/rv11/  į /luckfox-pico/sysdrv/source/uboot/rkbin/tools
2. išekstraktinam reikšmes į dump_params.txt
  ./ddrbin_tool -g dump_params.txt rv1106_ddr_924MHz_v1.10.bin

3. surandam uart reikšmes
  ...
  uart id=2
  uart iomux=1
  uart baudrate=115200
  ...

4. pakeičiam į 
  ...
  uart id=5
  uart iomux=2
  uart baudrate=115200
  ...

5. sukišam atgal į bin failą
  ./ddrbin_tool dump_params.txt rv1106_ddr_924MHz_v1.10.bin

6. pakoreguotą bin failą užkopinam atgal į /luckfox-pico/sysdrv/source/uboot/rkbin/bin/rv11/

7. naujas CONSOLE uartas turi buti uždisablintas DTS'e

8. TODO (nežinau kodėl)  /dev/ttyFIQ0   atsiranda tik jei &uart2 uždisablintas nors rkbin' uartas nustatytas -> uart id=3; uart iomux=1; uart baudrate=115200



/luckfox-pico/sysdrv/source/uboot/u-boot/arch/arm/dts/rv1106-u-boot.dtsi