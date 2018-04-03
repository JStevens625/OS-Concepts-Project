#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//Syscalls needed for users to call
#define SHARED_PAGES 4
void *shared_page[SHARED_PAGES];
int shared_counter[SHARED_PAGES];

int
sys_shmem_access(void)
{
  int pgn;
  char* virtaddr;
  argint(0, &pgn);
  argstr(0, &virtaddr);
  for (int i = 0; i < 4; i++) {
    shared_page[i] = setupkvm();
    allocuvm(shared_page[i], 0, PGSIZE);
    shared_counter[i] = 0;
  }
  shared_counter[pgn]++;
  proc->token = pgn;
  proc->shpg = shared_page[pgn];
  proc->virtaddr = virtaddr;
  return 0;
}

int
sys_shmem_count(void)
{
  return shared_counter[proc->token];
}

int
sys_shmem_retrieve(void)
{
  return (int) uva2ka(proc->shpg, proc->virtaddr);
}
