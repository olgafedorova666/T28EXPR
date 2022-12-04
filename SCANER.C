#include "SCANER.h"
int Scanner(QUEUE *Q, char *s)
{
  TOK T;
  int x = 0;
  int denum = 1;
  while(*s != 0)
  {
    switch(*s)
    {
    case' ':
    case'\t':
    case'\n':
      s++;
      continue;
    case'+':
    case'-':
    case'*':
    case'/':
    case'^':
    case'%':
    case')':
    case'(':
      T.Id = TOK_OP;
      T.Op = *s++;
      break;
    case'0':
    case'1':
    case'2':
    case'3':
    case'4':
    case'5':
    case'6':
    case'7':
    case'8':
    case'9': 
    T.Id = TOK_NUM;
    T.Num = 0;
    while(*s >= '0' && *s <= '9')
      T.Num = T.Num * 10 + (*s++ - '0');
    if(*s == '.')
    {
      *s++;
      while(*s >= '0' && *s <= '9')
        T.Num = T.Num + (*s++ - '0') / (denum *= 10);
    }
    
    break;
    default:
      printf("Error: unrecornized character%c\n", *s);
      return 0;
    }
    if(!Put(Q, T))
    {
      printf("Error: not enought memory\n");
      return 0;
    }
  }
  return 1;
}