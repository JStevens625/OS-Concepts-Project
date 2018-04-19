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

int thread_create(void(*start_routine)(void*), void *arg){
  int i = clone(start_routine,arg,malloc(4096));
  //printf(1,"Here: %d\n", i);
}

int thread_join(){
  void *stack;
  join(&stack);
  return stack;
}

void testforthreads(void* arg){
  for (size_t i = 0; i < 100000; i++) {
    printf(1, "Child Running\n");
  }
  exit();
}

int main(int argc, char *argv[]){
  void* arg[] = {
    0
  };
  for (size_t i = 0; i < 100000; i++) {
    printf(1, "Parent Running\n");
  }
  thread_create(testforthreads,arg);
  thread_join();
 exit();
}
