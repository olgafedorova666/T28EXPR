
#include "SCANER.h"
void main(void)
{
  char str[256];
  QUEUE Q = {NULL, NULL};
  QUEUE QRES = {NULL, NULL};

  STACK S = {NULL};
  printf("Put string \n");
  GetStr2(str);
  if (Scanner(&Q, str))
  {
    printf("Queue:");
    Display(Q.Head);
  }
  else 
    printf("Scaner error\n");
  if (Parser2(&Q, &QRES))
  {
    printf("Queue:");
    Display(QRES.Head);
  }
  else
    printf("Error\n"); 

  if(Eval(&QRES, &S))
  {
    printf("Result:");
    Display(S.Top);
  }
  else
    printf("Eval error\n");
  _getch();
}