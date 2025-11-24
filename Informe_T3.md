# Informe – Tarea 3: Protección de Lectura en xv6
**Integrantes:** Daniel Abrego — Fernando Rojas

## Objetivo
Implementar un mecanismo en xv6 que permita deshabilitar la lectura de memoria de usuario mientras mantiene la escritura habilitada, con el fin de proteger datos sensibles como claves o credenciales.  
Se desarrollaron las funciones `mrdprotect()` y `munrdprotect()` que modifican el bit `PTE_R` en la tabla de páginas del proceso.

## Archivos modificados
- **kernel/vm.c:** implementación de las funciones `mrdprotect()` y `munrdprotect()`.
- **kernel/syscall.h / syscall.c / sysproc.c:** registro y manejo de las nuevas syscalls.
- **user/user.h / usys.pl:** prototipos y stubs en espacio de usuario.
- **user/rdprotect_test.c:** creación del programa de prueba.
- **Makefile:** agregado `_rdprotect_test` en la lista de programas de usuario.

## Funcionamiento
- `mrdprotect(void *addr, int len)`:
  - Limpia el bit `PTE_R` en las PTE correspondientes al rango `[addr, addr + len * PGSIZE)`.
  - Deshabilita el permiso de lectura pero mantiene escritura y ejecución.
- `munrdprotect(void *addr, int len)`:
  - Restaura el bit `PTE_R`, reactivando la lectura de la memoria afectada.
- Ambas funciones realizan validaciones:
  - La dirección debe estar alineada a página (`PGSIZE`).
  - `len` debe ser mayor que 0.
  - Las PTE deben ser válidas (`PTE_V`) y de usuario (`PTE_U`).
  - No se permite modificar memoria del kernel.
- Se usa `sfence_vma()` para actualizar la TLB tras modificar permisos.

## Pruebas
1. **Compilación:**
   ```bash
   make clean
   make qemu

2. **Ejecución en el shell de xv6:**
    ```bash
    $ rdprotect_test

3. **Resultado esperado:**
    - La función mrdprotect() deshabilita la lectura pero mantiene la escritura.

    - Intentar leer desde la página protegida provoca un fallo de página (panic o kill del proceso).

    - Tras ejecutar munrdprotect(), la lectura vuelve a estar habilitada normalmente.

## Dificultades
- **Comprensión del manejo de permisos:** fue necesario revisar cómo xv6 administra los bits de permisos (R/W/X/U/V) dentro de la tabla de páginas.
- **Uso correcto de `walk()`:** se requirió obtener el PTE exacto de cada página sin alterar las demás.
- **Actualización del TLB:** al inicio los cambios no surtían efecto hasta aplicar `sfence_vma()`.
- **Validaciones de seguridad:** asegurar que las direcciones fueran de usuario y estuvieran alineadas a páginas fue clave para evitar modificar memoria del kernel.

/// agregar lo de argint() 
