#include "types.h"
#include "stat.h"
#include "user.h"

typedef struct lock_t{
 int flag;
} lock_t;

void lock_init(lock_t* mutex){
  mutex->flag = 0;
}

void lock_acquire(lock_t* mutex){
  while (mutex->flag == 1) {
    ;
  }
  mutex->flag = 1;
}

void lock_release(lock_t* mutex){
  mutex->flag = 0;
}

int thread_create((*start_routine)(void*), void *arg){
  clone(start_routine,arg,malloc(4096));
}

int thread_join(){
  void *stack;
  join(&stack);
  return stack;
}
