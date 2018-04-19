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

//System Calls for Threading
int
sys_clone(void(*fcn)(void*),void *arg, void *stack)
{
 //Define the function parameters
 void (*fcn)(void*);
 void *arg;
 void *stack;

 //Check if invalid
 if(argptr(0,(char**)&fcn, sizeof(void*)) < 0 ){
  return -1;
 }
 if(argptr(1,(char**)&arg, sizeof(void*)) < 0){
  return -1;
 }
 if(argptr(2,(char**)&stack, 4096) < 0){
  return -1;
 }
 //Pulled from fork()
 int i, pid;
 struct proc *np;

 // Allocate process.
 if((np = allocproc()) == 0)
   return -1;

 // Copy process state from p.
 if((np->pgdir = copyuvm(proc->pgdir, proc->sz)) == 0){
   kfree(np->kstack);
   np->kstack = 0;
   np->state = UNUSED;
   return -1;
 }
 np->sz = proc->sz;
 np->parent = proc;
 *np->tf = *proc->tf;

 // Clear %eax so that fork returns 0 in the child.
 np->tf->eax = 0;

 for(i = 0; i < NOFILE; i++)
   if(proc->ofile[i])
     np->ofile[i] = filedup(proc->ofile[i]);
 np->cwd = idup(proc->cwd);

 pid = np->pid;
 np->state = RUNNABLE;
 safestrcpy(np->name, proc->name, sizeof(proc->name));
 return pid;

 return 0;
}

int
sys_join(void **stack)
{
 void** stack;
 if(argptr(0, (char**)&stack, sizeof(void*)) < 0){
  return -1;
 }
 //Pulled from wait()
 struct proc *p;
 int havekids, pid;

 acquire(&ptable.lock);
 for(;;){
   // Scan through table looking for zombie children.
   havekids = 0;
   for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
     if(p->parent != proc)
       continue;
     havekids = 1;
     if(p->state == ZOMBIE){
       // Found one.
       pid = p->pid;
       kfree(p->kstack);
       p->kstack = 0;
       freevm(p->pgdir);
       p->state = UNUSED;
       p->pid = 0;
       p->parent = 0;
       p->name[0] = 0;
       p->killed = 0;
       release(&ptable.lock);
       return pid;
     }
 return 0;
}
