
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RANGE 1000 

int fun(int bottom, int top)
{
  int number = 0;
  int divisor = 2;

  for(number = bottom; number <= top; number++) {
    for(divisor = 2; divisor < number/2; divisor++) {
      if(number % divisor == 0) {
        break;
      }
    }
    if(divisor >= number/2) {
      printf("%d ", number);
    }
  }

  return 0;
}

int forks(int st , int end)
{  
  pid_t pid;

  if(end - st > RANGE){
    if((pid = fork()) < 0) {
      printf("fork error!!");
    } else if (pid == 0) {
      printf("I am a child process.\n");
      forks(st + RANGE , end); 
    } else {
      printf("I have a child with id=%d\n",pid);
      fun(st , st + RANGE);
    }
  } else {
    fun(st , end);
  }
  
  return 0;
}

int main(int argc, char *argv[])
{
  int top = atoi(argv[2]);
  int bottom = atoi(argv[1]);
  
  //fun(3,10);
  forks(bottom, top);
  
  exit(0);
    
  return 0;
}

