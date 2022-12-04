#include "SCANER.h"
double Eval(QUEUE *Q, STACK *S)
{
  TOK T, A, B;
  while(Get(Q, &T))
  {
    if (T.Id == TOK_NUM)
      Push(S, T);
    else
    {
      if(T.Op == '@')
      {
        Pop(S, &A);
        A.Num *= (-1);
        Push(S, A);
      }
      else
      {
        Pop(S, &A);
        Pop(S, &B);
        switch(T.Op)
        {
        case'+':
          A.Num += B.Num;
          break;
        case'-':
          A.Num -= B.Num;
          break;
        case'*':
          A.Num *= B.Num;
          break;
        case'/':
          A.Num /= B.Num;
          break;
        case'^':
          A.Num = pow(B.Num, A.Num);
          break;
        case'%':
          A.Num = fmod(B.Num, A.Num);
          break;
        }
        Push(S, A);
      }
    }
  }
  return 1;
}