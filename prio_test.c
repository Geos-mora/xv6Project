#include "types.h"
#include "stat.h"
#include "user.h"

void
trabajo(char *nombre)
{
  int i, j;
  for(i = 0; i < 50; i++){
    printf(1, "[%s] pid=%d iter=%d\n", nombre, getpid(), i);
    for(j = 0; j < 10000000; j++); // bucle para consumir CPU
  }
}

int
main(void)
{
  int prios[3] = {5, 10, 15};
  char *nombres[3] = {"P1","P2","P3"};
  int i, pid;

  printf(1, "Iniciando prueba del scheduler por prioridades...\n");

  for(i = 0; i < 3; i++){
    pid = fork();
    if(pid == 0){
      setpriority(getpid(), prios[i]);
      printf(1, "Proceso %s: PID=%d prioridad=%d\n",
            nombres[i], getpid(), prios[i]);
      trabajo(nombres[i]);
      exit();
    }
  }

  while(wait() > 0);
  printf(1, "Prueba finalizada.\n");
  exit();
}
