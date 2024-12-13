# Galaga Game Project

## Descripción

Este proyecto es una implementación del clásico juego **Galaga** utilizando **SFML** (Simple and Fast Multimedia Library). El juego incluye movimiento del personaje, disparos, enemigos generados dinámicamente y una pantalla de inicio y fin. Sigue una estructura modular con clases bien definidas en un entorno de desarrollo organizado.

---

## Estructura del Proyecto

El proyecto está organizado en las siguientes carpetas:

- **/bin**: Contiene los archivos ejecutables generados.
- **/docs**: Incluye documentación del proyecto, diagramas de clases y manuales de usuario.
- **/data**: Contiene recursos como imágenes, fuentes y música necesarios para el juego.
- **/include**: Archivos de encabezado (.hpp) que definen las clases principales del juego.
- **/src**: Archivos fuente (.cpp) con las implementaciones de las clases y la lógica principal.
- **Makefile**: Archivo que permite compilar y ejecutar fácilmente el proyecto.

---

## Requisitos del Sistema

- **Sistema Operativo**: Windows (compilado con MinGW64 utilizando MSYS2)
- **Dependencias**:
  - SFML 2.5+
  - MinGW64 para compilar en Windows

---

## Cómo Configurar el Proyecto

### Instalación de Herramientas

1. **Visual Studio Code**  
   Descargar e instalar desde este [enlace](https://code.visualstudio.com/).

2. **MSYS2 (Windows)**  
   Descargar e instalar desde este [enlace](https://github.com/msys2/msys2-installer/releases/download/2023-05-26/msys2-x86_64-20230526.exe).  

   No modificar ninguna opción al momento de la instalación para evitar problemas de configuración.  
   Agregar los siguientes directorios al `PATH` del sistema y reiniciar el equipo:
   - `C:\msys64\mingw64\bin`
   - `C:\msys64\usr\bin`

3. **Git**  
   Descargar desde este [enlace](https://git-scm.com/).

4. **Github Desktop**  
   Descargar el cliente para clonar repositorios desde este [enlace](https://desktop.github.com/).

---

## Instalación de Dependencias

En una terminal de **MSYS2**, ejecutar los siguientes comandos:

### Instalar compiladores y herramientas de desarrollo
```bash
pacman -S --needed base-devel mingw-w64-x86_64-toolchain