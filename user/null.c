#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
  int *p = 0; //Creates Integer Pointer to 0
  int *q = NULL; //Creates Integer Pointer to NULL
  printf(1, "Dereference p:[%x]\n", *p); //Dereference
  printf(1, "Dereference q:[%x]\n", *q); //Dereference
  exit();
}
