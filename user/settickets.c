#include "types.h"
#include "stat.h"
#include "user.h"
#include <stdio.h>
// running system call howmanysys()
int main(void){
  int numberoftickets;
  printf("Please input number of tickets: ");
  scanf("%d\n", &numberoftickets);
  if (numberoftickets >= 1) {
    return 0;
  }
  else{
    return -1;
  }
}
