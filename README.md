# RedBall!

El proyecto esta desarrollado sobre MinGW64 utilizando Msys2
y como editor se esta utilizando Visual Studio Code

## Como ejecutar el programa

Instalar todas las dependencias descritas abajo y dentro de una terminal de vscode ejecutar:

> make runmain

## Controles

Movimiento derecha "->"
Movimiento izquierda "<-"
Salto "space"

## Objetivo

Llegar a la plataforma amarilla lo mas rapido posible!

# Requerimientos para compilar el programa

### Visual studio code
Descargar e instalar vscode en el siguiente [Enlace.](https://code.visualstudio.com/)

### MSYS2 (Windows)

Instalar Msys2 usando el siguiente [Enlace.](https://github.com/msys2/msys2-installer/releases/download/2023-05-26/msys2-x86_64-20230526.exe)

No modificar ningua opcion al momento de intalacion o podrian variar las configuraciones.

Una vez instalado es necesario agregar los siguientes directorios al path de windows y reiniciar.

> C:\msys64\mingw64\bin

> C:\msys64\usr\bin

## Librerias utilizadas (Msys2)

Ejecutar los siguientes comandos en la terminal de msys2 para instalar las dependencias necesarias

### DevTools
Compiladores y herramientas necesarias para el desarrollo.

https://code.visualstudio.com/docs/cpp/config-mingw
> pacman -S --needed base-devel mingw-w64-x86_64-toolchain

### SFML
https://packages.msys2.org/package/mingw-w64-x86_64-sfml
> pacman -S mingw-w64-x86_64-sfml

### Box2D simulaciones de fisica - C++
https://box2d.org/documentation/
https://packages.msys2.org/package/mingw-w64-x86_64-box2d?repo=mingw64
pacman -S mingw-w64-x86_64-box2d

## Assets utilizados

### sky background(FondoCielo) por "Paulina Riva"
https://opengameart.org/content/sky-background

### grass tiles(grass_0) por "Marta Nowaczyk"
https://opengameart.org/content/grass-tiles-1

### 2 seamless lava tiles(Lava #4) por "LuminousDragonGames"
https://opengameart.org/content/2-seamless-lava-tiles

### Harold the Angry Man Face Ball(noFilter.png) por "Sterald gang"
https://www.rolimons.com/item/16067672998

### texture ice(tex_Ice) por "Jatenalle"
https://opengameart.org/content/texture-ice

### slime jump effect(slime_jump) por "KobatoGames"
https://opengameart.org/content/slime-jump-effect

### one(music) por "pheonton"
https://opengameart.org/content/one

### DS-Digital(DS-DIGI) por "Dusit Supasawat"
https://www.dafont.com/es/ds-digital.font

### RedBall por Evgeniy "Eugene" Fedoseev
https://www.numuki.com/game/red-ball-1/