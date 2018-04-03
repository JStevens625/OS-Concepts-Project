#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  char virtaddr = 1000;
  void *ptr;

  ptr = shmem_access(3, &virtaddr);
  if(ptr == NULL){
    printf(1,"Failed1\n");
  }
  int pid = fork();
  if (pid < 0) {
    printf(1,"Failed2\n");
  }
  else if (pid == 0){
    void *ptr2;

    ptr2 = shmem_access(3, &virtaddr);
    if (ptr2 == NULL) {
      printf(1,"Failed3\n");
    }
    if(ptr != ptr2){
      printf(1,"Failed4\n");
    }
    exit();
  }
  else{
    wait();
  }
  printf(1, "Passed\n");
  exit();
}
