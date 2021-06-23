#include <sched.h>
#include <stdio.h>
int main(int argc, char **argv)
{
  printf("Setting SCHED_RR and priority to %d\n",atoi(argv[1]));
  struct sched_param param;
  param.sched_priority = atoi(argv[1]);
  sched_setscheduler(0, SCHED_RR, &param);
  int n = 0;
  while(1) {
    n = n + 1;
    if (!(n % 10000000)) {
      printf("Inst:%s RR Prio %d running (n=%d)\n",argv[2], atoi(argv[1]), n);
    }
  }
}
