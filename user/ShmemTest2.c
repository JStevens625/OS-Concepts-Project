#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  void* virtaddr = 1000;
  shmem_access(0, &virtaddr);
  char *p = shmem_retrieve();
  p = "Call This String!";
  int* q;
  q = 0;
  int pid = fork();
  if(pid > 0) {
    printf(1, "I am the parent\n");
    printf(1, "Address: %p\n", p);
    printf(1, "Content: %s\n", p);
    //printf("Count of Processes: %d\n", shmem_count());
    wait();
    exit();
  }
  if (pid == 0) {
    printf(1, "I am the child\n");
    printf(1, "Address %p\n", p);
    printf(1, "Content %s\n", p);
    //printf("Count of Processes: %d\n", shmem_count());
    exit();
  }
  else {
    printf(1, "There was an error forking this process\n");
  }
  exit();
}
