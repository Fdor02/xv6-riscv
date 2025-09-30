# Informe – Tarea 1: Llamadas al sistema en xv6
**Integrantes:** Daniel Abrego — Fernando Rojas

---

## Objetivo
Implementar dos nuevas llamadas al sistema en xv6:
- `getppid()`: retorna el PID del proceso padre.
- `getancestor(int k)`: retorna el PID del ancestro *k*-ésimo (0=yo, 1=padre, 2=abuelo, …, −1 si no existe).  
Además, crear un programa de prueba llamado `yosoytupadre`.

---

## Archivos modificados
- **Makefile**: agregar `_yosoytupadre` en `UPROGS`.
- **kernel/**
  - `syscall.h`: agregar números de syscall.
  - Observación clave: estos números **deben coincidir** con los índices utilizados en la tabla de `syscall.c`.
  - `syscall.c`: mapear los nuevos syscalls.
  - `sysproc.c`: implementar `sys_getppid` y `sys_getancestor`.
  - Se recorrió la cadena de padres `k` pasos; si el ancestro existe se retorna su `pid`, de lo contrario `-1`.
- **user/**
  - `user.h`: agregar prototipos.
  - `usys.pl`: generar stubs de syscalls.
  - `yosoytupadre.c`: programa de prueba creado por nosotros.

---

## Pruebas
1. Compilamos con:
   ```bash
   make clean
   make qemu

## En la shell de xv6
2. 
    $ yosoytupadre
    yo=<pid_actual>, ppid=<pid_padre>
    getancestor(0) = <pid_actual>
    getancestor(1) = <pid_padre>
    getancestor(2) = <pid_abuelo>    # si existe; de lo contrario -1
    getancestor(3) = -1              # esperado si no existen más ancestros


3. Resultado: 

    getppid() retorna el PID del padre del proceso que invoca.

    getancestor(k) respeta la semántica 0→yo, 1→padre, 2→abuelo; y −1 cuando no hay tantos ancestros.

## Dificultades

Coordinación entre múltiples archivos (kernel/user/Makefile) al principio generó confusión.

Error inicial en sys_getancestor al usar argint(0, &k); por definición incorrecta. Se corrigió ajustando firma y lectura del argumento.

int k;
if (argint(0, &k) < 0) return -1;


## Conclusión

Se implementaron correctamente las llamadas al sistema getppid() y getancestor(int) y se integró el programa de prueba yosoytupadre.c al userland. Las pruebas mostraron la funcionalidad esperada. Los principales desafíos estuvieron en coordinar cambios consistentes entre varios archivos del kernel y del userland, y en la lectura segura de argumentos desde espacio de usuario.


