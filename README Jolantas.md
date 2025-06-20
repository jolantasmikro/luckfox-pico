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
  In firs time: (make luckfox_pico_defconfig)
make menuconfig
```
1. Add minicom
2. Add iftop 
3. Add owerlays path ../../../../overlays/buildroot/   (System configuration --> ... Root filesystem overlay directories)
4. Add pppd  Target packages → Networking applications
5. Add cJSON
5. Add libuci (automatiškai prisideda ir libubox, kuris turi daug gerų funkcijų)
6. Add libcurl
7. -> Target packages                                                                                                                                                                                                                    │
    │ (2)   -> Networking applications
       [ ] mosquitto
8.  Target packages  --->
      Libraries  --->
        Database  --->
          [*] sqlite                                                                                                            
            [ ]   Additional query optimizations (stat4) (NEW)                                                                       
            [ ]   Enable convenient access to meta-data about tables and queries (NEW) 
            [*]   Enable version 3 of the full-text search engine             
            [ ]   Enable the JSON extensions for SQLite (NEW)                 
            [ ]   Enable sqlite3_unlock_notify() interface (NEW)   
            [ ]   Set the secure_delete pragma on by default (NEW)           
            [ ]   Disable fsync (NEW)
9.  Prompt: libmodbus                                                                                                                                                                                                                   
  │   Location:                                                                                                                                                                                                                           
  │     -> Target packages                                                                                                                                                                                                              
  │       -> Libraries                                                                                                                                                                                                                   
  │ (4)     -> Networking
             [*] libmodbus
10. Prompt: libev                                                                                                                                                                                                                           
     Location:                                                                                                                                                                                                                     
       -> Target packages                                                                                                                                                                                                        
         -> Libraries                                                                                                                                                                                                            
   (1)     -> Other
11. Prompt: host mosquitto (mosquitto_passwd)                                                   │
  │   Location:                                                                                 │
  │     -> Host utilities
      [*] host mosquitto (mosquitto_passwd)

12. Prompt: libwebsockets                                                                       │
  │   Location:                                                                                 │
  │     -> Target packages                                                                      │
  │       -> Libraries                                                                          │
  │ (1)     -> Networking
     [*] libwebsockets
     -*- paho-mqtt-c                                                                 │ │
     [*] paho-mqtt-cpp





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
