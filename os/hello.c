#include <stdio.h>

int main(){
    char str[] = "HELLO WORLD!";
    char *p = str;
    
    while(*p)
    {
      if(*p >= 'A' && *p <= 'Z'){
        *p += 'a'-'A';
      }
      p++;
    }
    
    printf("%s\n",str);
    return 0;
}
