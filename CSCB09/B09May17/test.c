#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

char * st = malloc(31);
// reading a string into st
// you may assume that not more than 30 characters are read
scanf("%s", &st);
printf("%s\n", st);
return 0;
}
