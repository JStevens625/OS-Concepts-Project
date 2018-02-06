#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

int counter = 0;

int
sys_fork(void)
{
  counter++;
  return fork();
}

int
sys_exit(void)
{
  exit();
  counter++;
  return 0;  // not reached
}

int
sys_wait(void)
{
  counter++;
  return wait();
}

int
sys_kill(void)
{
  counter++;
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
    counter++;
  return kill(pid);
}

int
sys_getpid(void)
{
  counter++;
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    counter++;
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    counter++;
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    counter++;
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      counter++;
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  counter++;
  return 0;
}

//Custom System Count Code
int
sys_howmanysys(void)
{
  cprintf("There has been %d many system calls\n", counter);
  counter++;
}
//Custom System Count Code end.


// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  counter++;
  return xticks;
}
