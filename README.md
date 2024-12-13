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

# Manual del Juego: Sky Rider

## Introducción
Sky Rider es un juego de estilo arcade en el que controlas una nave espacial para esquivar enemigos, disparar proyectiles y obtener la mayor puntuación posible. Este manual te guiará en los controles, reglas del juego y características principales.

---

## Controles

### Movimiento de la nave
- **Flecha izquierda (←)** o **tecla 'A'**: Mover la nave hacia la izquierda.
- **Flecha derecha (→)** o **tecla 'D'**: Mover la nave hacia la derecha.
- **Flecha arriba (↑)** o **tecla 'W'**: Mover la nave hacia arriba.
- **Flecha abajo (↓)** o **tecla 'S'**: Mover la nave hacia abajo.

### Disparo
- **Barra espaciadora**: Disparar proyectiles hacia los enemigos.

### Interacción con el juego
- **Tecla Enter**: 
  - Desde la pantalla inicial: Comienza el juego.
  - Después de una pantalla de "Game Over": Reinicia el juego.

---

## Reglas del Juego

### Objetivo principal
- Sobrevive el mayor tiempo posible y acumula puntos al destruir enemigos.

### Proyectiles enemigos
- Los enemigos disparan proyectiles periódicamente. Si un proyectil enemigo impacta tu nave, aparecerá la pantalla de "Game Over".

### Generación de enemigos
- Los enemigos se generan automáticamente desde el borde derecho de la pantalla y se mueven hacia la izquierda.

### Game Over
- Al ser impactado por un proyectil enemigo, aparecerá la pantalla de "Game Over".
- Presiona **Enter** para reiniciar el juego y volver a la pantalla de inicio.

---

## Características

1. **Diseño gráfico**:
   - Fondos visualmente atractivos tanto para la pantalla de inicio como para el juego principal.
   - Enemigos y proyectiles diseñados con sprites personalizados.

2. **Música**:
   - Una banda sonora de fondo que se reproduce en bucle para una experiencia inmersiva.

3. **Puntuación**:
   - El puntaje se basa en el tiempo de supervivencia. Se muestra en la esquina superior izquierda durante el juego.

4. **Dificultad**:
   - Los enemigos aparecen con intervalos regulares, y sus proyectiles aumentan la dificultad con el tiempo.

---

## Resolución de Problemas

1. **Si el juego no inicia**:
   - Asegúrate de que todos los archivos (texturas, música, fuentes) estén en las rutas correctas según el código.

2. **La música no se escucha**:
   - Verifica que el archivo de audio exista en la carpeta `assets/music` con el nombre exacto mencionado en el código.

3. **Comportamientos inesperados**:
   - Revisa el código fuente en busca de errores en las funciones relacionadas.

---

¡Buena suerte y disfruta jugando Sky Rider!
