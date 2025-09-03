# INFORME DE INSTALACIÓN – XV6  
**Tarea 0**  
**Integrantes:** Daniel Abrego – Fernando Rojas  

---

## Introducción  
El objetivo de esta tarea fue instalar el sistema operativo educativo **xv6** en nuestra máquina local, ejecutarlo en QEMU y documentar el proceso, incluyendo los pasos realizados, los problemas encontrados y sus soluciones.  

---

## Pasos realizados  

1. **Fork y clonación del repositorio**  
   - Realizamos un fork del repositorio oficial entregado en clases.  
   - Posteriormente, lo clonamos de manera local utilizando **Visual Studio Code** y Git:  
     ```bash
     git init
     git clone https://github.com/Fdor02/xv6-riscv
     ```

2. **Creación de una nueva rama**  
   - Seleccionamos el directorio del repositorio clonado y creamos una rama para trabajar:  
     ```bash
     cd xv6-riscv
     git checkout -b grupo7_t0
     ```

3. **Instalación de WSL**  
   - Como parte del entorno, instalamos **Windows Subsystem for Linux (WSL)**:  
     ```bash
     wsl --install
     ```

4. **Configuración inicial de Ubuntu en WSL**  
   - Ingresamos a WSL y actualizamos los paquetes:  
     ```bash
     wsl
     sudo apt update
     ```

5. **Instalación de dependencias y toolchain**  
   - Instalamos los paquetes básicos y las herramientas necesarias:  
     ```bash
     sudo apt install build-essential qemu-system-x86 gdb -y
     ```
   - Debido a errores iniciales (por no abrir correctamente el terminal de WSL), repetimos la instalación.  
   - Instalamos los paquetes específicos de RISC-V:  
     ```bash
     sudo apt install riscv64-unknown-elf-gcc 
     sudo apt install qemu-system-riscv64 
     ```

6. **Verificación de instalaciones**  
   - Confirmamos las instalaciones con la opción `--version`:  
     ```bash
     riscv64-unknown-elf-gcc --version
     qemu-system-riscv64 --version
     ```

7. **Compilación y prueba de xv6**  
   - Ejecutamos el comando:  
     ```bash
     make qemu
     ```
   - Dentro de xv6 probamos los comandos solicitados en la tarea:  
     ```
     $ ls
     $ echo "Hola xv6"
     $ cat README
     ```
   - Adjuntamos la captura de pantalla como evidencia (pantallazo con los comandos anteriores ejecutados).  

---

## Problemas encontrados  

- **Error al compilar con `make qemu`:**  
    gcc -I. -o mkfs/mkfs mkfs/mkfs.c
    make: gcc: No such file or directory
    make: *** [Makefile:117: mkfs/mkfs] Error 127

    Este error se debía a que **gcc no estaba instalado correctamente**.  

    - **Causa adicional:** instalación incompleta de WSL la primera vez, lo que generó fallos en la configuración inicial.  

---

## Solución aplicada  

- Investigamos en línea y encontramos que instalando el paquete **build-essential** se resolvía el problema, ya que incluye `gcc` y otros compiladores necesarios.  
- Reinstalamos correctamente WSL, abrimos el terminal de Ubuntu desde WSL y ejecutamos nuevamente las instalaciones.  
- Con esto logramos compilar y ejecutar xv6 correctamente.  

    ---

## Conclusión  

La instalación de xv6 requirió resolver errores relacionados con dependencias ausentes y la configuración de WSL. Finalmente, logramos ejecutar `make qemu` con éxito y verificar el funcionamiento del sistema operativo mediante los comandos requeridos.  

Se adjunta captura de pantalla como evidencia de la ejecución de xv6 en QEMU.  
*Adjunta en el correo enviado al profesor*
