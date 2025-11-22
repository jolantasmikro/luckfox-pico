# Norėdami įjungti WDT (watchdog timer) jūsų DTS faile ir perkompiliuoti DTB, atlikite šiuos veiksmus:
# Device Tree Configuration

## WDT (Watchdog Timer) įjungimas

### 1. Redaguokite DTS failą

Failas: `sysdrv/source/kernel/arch/arm/boot/dts/rv1106g-luckfox-pico-pro-max_ser3net.dts`

```dts
// ...existing code...

/**********RTC**********/
&rtc {
    status = "okay";
};

/**********WDT**********/
&wdt {
    status = "okay";
};
```

### 2. Perkompiliuokite device tree

#### Vieno DTB kompiliavimas:

```bash
cd /home/jok/LuckFox/ser3net/luckfox-pico/sysdrv/source/kernel
make ARCH=arm rv1106g-luckfox-pico-pro-max_ser3net.dtb
```

#### Visų DTB kompiliavimas:

```bash
cd /home/jok/LuckFox/ser3net/luckfox-pico/sysdrv/source/kernel
make ARCH=arm dtbs
```

#### Naudojant build.sh:
#### ⚡ MAn suveikė gerai: Naudojant build.sh
```bash
cd /home/jok/LuckFox/ser3net/luckfox-pico
./build.sh kernel
```

### WDT konfigūracija

Pagal `rv1106.dtsi` failą, WDT jau turi visus reikalingus nustatymus:

- **Compatible**: `rockchip,rv1106-wdt`, `snps,dw-wdt`
- **Clocks**: `TCLK_WDT_NS`, `PCLK_WDT_NS`
- **Interrupts**: `GIC_SPI 46`

> **Pastaba**: Tiesiog nustatę `status = "okay"` įjungsite watchdog timer funkcionalumą.

1. Redaguokite DTS failą:

```
    // ...existing code...

    /**********RTC**********/
    &rtc {
        status = "okay";
    };

    /**********WDT**********/
    &wdt {
        status = "okay";
    };
```

2. Perkompiliuokite device tree:
```
cd /home/jok/LuckFox/ser3net/luckfox-pico/sysdrv/source/kernel
make ARCH=arm rv1106g-luckfox-pico-pro-max_ser3net.dtb
```

3. Arba perkompiliuokite visą kernel su device tree:
```
cd /home/jok/LuckFox/ser3net/luckfox-pico/sysdrv/source/kernel
make ARCH=arm dtbs
```

4. Arba naudokite build.sh:
```
cd /home/jok/LuckFox/ser3net/luckfox-pico
./build.sh kernel
```

Pagal rv1106.dtsi failą, WDT jau turi visus reikalingus nustatymus:

Compatible: rockchip,rv1106-wdt, snps,dw-wdt
Clocks: TCLK_WDT_NS, PCLK_WDT_NS
Interrupts: GIC_SPI 46
Tiesiog nustatę status = "okay" įjungsite watchdog timer funkcionalumą.