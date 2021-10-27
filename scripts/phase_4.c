#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int func4(int inputNumber)
{
  int nb1;
  int nb2;
  if (inputNumber < 2) {
    nb2 = 1;
  }
  else {
    nb1 = func4(inputNumber + -1);
    nb2 = func4(inputNumber + -2);
    nb2 = nb2 + nb1;
  }
  return nb2;
}

int main(int ac, char **av)
{
  int param_1 = atoi(av[1]);
  printf("%d", func4(param_1));
}