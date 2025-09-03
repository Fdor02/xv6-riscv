Tarea 0
Daniel Abrego -- Fernando Rojas
INFORME DE INSTALACION XV6

Obtuve un error al intentar correr el make qemu por no tener instalado el gcc, ademas de no haber instalado correctamente wsl, cosa que pensaba q ya habia hecho

Pasos seguidos: 
1- Lo primero que hicimos fue hacer un fork al repositorio entregado en clases, para luego clonarlo localmente , en nuestro caso usando Visual Studio Code.

git init
git clone https://github.com/Fdor02/xv6-riscv

2- Una vez en hecho esto lo siguiente que hicimos fue seleccionar el directorio de este repositorio y crear una nueva rama desde la cual trabajar a la que llamamos grupo7_t0
cd
git checkout -b grupo7_t0

3- Luego instalamos wsl
wsl --install

4- Abrimos wsl y ubuntu
wsl
sudo apt update

5- Instalamos nuestro toolchain con los nombres default recomendados
sudo apt install build-essential qemu-system-x86 gdb -y

Esto lo hicimos dos veces por errores obtenidos ya que no abrimos correctamente nuestro terminal con wsl la primera vez
sudo apt riscv64-unknown-elf-gcc 
sudo apt qemu-system-riscv64 

6- Verificamos las instalaciones con el comando --version

7- Compilamos con make qemu y luego usamos los comandos solicitados por la tarea para demostrar su funcionalidad (se adjunta pantallazo)

Aqui cabe mencionar que obtuvimos un error en la instalacion obteniendo el siguiente output cuando usabamos el comando make qemu:
gcc -I. -o mkfs/mkfs mkfs/mkfs.c
make: gcc: No such file or directory
make: *** [Makefile:117: mkfs/mkfs] Error 127

Para esto encontramos en internet que con build-essential podiamos descargar correctamente todo lo necesario y hacerlo funcionar.