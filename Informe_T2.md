# Informe – Tarea 2: Lottery Scheduling en xv6
**Integrantes:** Daniel Abrego — Fernando Rojas
**GRUPO:** 7

---

## Objetivo
Implementar un nuevo planificador de procesos basado en **Lottery Scheduling** en xv6, reemplazando el planificador Round-Robin.  
Cada proceso posee una cantidad de *tickets* que determina su probabilidad de ser elegido para ejecución.  
Además, implementar la syscall `settickets(int)` para modificar los tickets del proceso actual y un contador `cpu_slices` para registrar cuántas veces fue seleccionado por la CPU.

---

## Archivos modificados
- **kernel/proc.h:** se agregaron los campos `int tickets;` y `int cpu_slices;` en `struct proc`.
- **kernel/proc.c:**  
  - Inicialización de `tickets` y `cpu_slices` en `allocproc()`.  
  - Se reemplazó el planificador por un *lottery scheduler*.  
  - Se agregó una función `krand()` para generar números pseudoaleatorios.  
- **kernel/syscall.h / syscall.c:** incorporación de la nueva syscall `settickets`.
- **kernel/sysproc.c:** implementación de `sys_settickets(int n)` asegurando mínimo un ticket.
- **user/user.h / usys.pl:** prototipo y stub de `settickets`.
- **user/demo.c:** nuevo programa de prueba que crea múltiples procesos con diferentes tickets.
- **Makefile:** agregado `_demo` a la variable `UPROGS` para compilar el programa de prueba.

---

## Funcionamiento
1. Cada proceso comienza con `tickets = 100` por defecto.
2. Los procesos pueden modificar sus tickets con `settickets(n)` (si `n < 1`, se asigna automáticamente 1).
3. El planificador realiza lo siguiente en cada iteración:
   - Suma la cantidad total de tickets de todos los procesos RUNNABLE.
   - Genera un número aleatorio entre `1` y `total`.
   - Recorre los procesos acumulando tickets hasta alcanzar el número aleatorio, eligiendo así al proceso ganador.
   - Incrementa el contador `cpu_slices` del proceso seleccionado.
4. El programa `demo` crea al menos 10 procesos con distintos tickets (`50*(i+1)`) y ejecuta trabajo en CPU para observar la distribución proporcional de tiempo.

## Pruebas
1. **Compilación y ejecución**
   ```bash
   make clean
   make qemu

2. **Dentro de la shell de xv6**

    $ demo
    child <pid> done (tickets=<n>)

3. **Resultado:**

  - Los procesos con más tickets fueron seleccionados más veces por el scheduler.
  - El conteo de cpu_slices mostró una distribución coherente con la cantidad de tickets.


## Dificultades
  - **Reemplazar el planificador:** fue necesario comprender el funcionamiento interno de `scheduler()` y cómo se cambia el estado de los procesos.
  - **Sincronización y validaciones:** se agregaron condiciones para evitar que `tickets` fuera menor que 1 y para continuar el ciclo cuando no hay procesos RUNNABLE.
  - **Generación aleatoria:** se implementó un generador LCG (`krand()`) para simular un número aleatorio sin librerías externas.
  - **Medición del comportamiento:** se usó `cpu_slices` y la salida del programa `demo` para validar el reparto proporcional de CPU.
  - **Exit:** Se rompió el comando para salir (`exit()`), el cuál no sabemos como ocurrió pero se reestableció posteriormente


*********Guardo aqui el codigo del scheduler, por si el otro falla:
kernel/proc.c --> Linea 434

void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();

  c->proc = 0;
  for(;;){
    // The most recent process to run may have had interrupts
    // turned off; enable them to avoid a deadlock if all
    // processes are waiting. Then turn them back off
    // to avoid a possible race between an interrupt
    // and wfi.
    intr_on();
    intr_off();

    int found = 0;
    for(p = proc; p < &proc[NPROC]; p++) {
      acquire(&p->lock);
      if(p->state == RUNNABLE) {
        // Switch to chosen process.  It is the process's job
        // to release its lock and then reacquire it
        // before jumping back to us.
        p->state = RUNNING;
        c->proc = p;
        swtch(&c->context, &p->context);

        // Process is done running for now.
        // It should have changed its p->state before coming back.
        c->proc = 0;
        found = 1;
      }
      release(&p->lock);
    }
    if(found == 0) {
      // nothing to run; stop running on this core until an interrupt.
      asm volatile("wfi");
    }
  }
}