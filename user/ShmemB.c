#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  shmem_access(0);
  char *p;
  printf("%c\n", *p);
  exit();
}
