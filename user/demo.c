#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int N = 10; // al menos 10
  for(int i=0; i<N; i++){
    int pid = fork();
    if(pid < 0){
      printf("fork failed\n");
      exit(1);
    }
    if(pid == 0){
      // Hijo: asigna tickets crecientes
      int t = 50 * (i + 1);
      settickets(t);
      // Trabajo "CPU-bound" para observar reparto
      volatile uint x = 0;
      for(volatile uint k=0; k<300000000; k++) x += k;
      printf("child %d done (tickets=%d)\n", getpid(), t);
      exit(0);
    }
  }
  // Padre: esperar a todos
  for(int i=0; i<N; i++) wait(0);
  exit(0);
}
