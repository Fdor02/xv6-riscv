Informe Tarea 1
Daniel Abrego -- Fernando Rojas

Archivos:
Para el funcionamiento de esta tarea fue necesario modificar los siguientes archivos:
Makefile
En la carpeta kernel:
    syscall.c
    syscall.h
    sysproc.c

En la carpeta de user:
    user.h
    usys.pl
    yosoytupadre.c (nosotros creamos este archivo)


Dificultades:
Orden en los archivos, al tener que trabajaren distintaos archivos y carpetas se dificultaba el orden
Al momento de definir la funcion de sys_getancestor (en kernel/sysproc.c) nos encontramos con un error al definir argint(0, &k); esto fue debido a que al momento de definir la funcion definimos de forma incorrecta el puntero de esta funcion