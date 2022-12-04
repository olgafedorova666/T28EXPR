#include "SCANER.h"
int Put(QUEUE *Q, TOK newdata)
{ 
  LIST *newEl;
  newEl = malloc(sizeof(LIST));
  if(newEl == NULL)
  {
    printf("Error");
    return 0;
  }
  else
  {
    newEl->T = newdata;
    newEl->Next = NULL;
    if(!Q->Head)
      Q->Head = Q->Tail = newEl;
    else
    {
      Q->Tail->Next = newEl;
      Q->Tail = newEl;
    }
  }
  return 1;
}


int Get(QUEUE *Q, TOK *oldData)
{
  LIST *tmp;
  if(Q->Head == NULL)
    return 0;
  *oldData = Q->Head->T;
  tmp = Q->Head;
  Q->Head = Q->Head->Next;
  free(tmp);
  if(Q->Head)
    Q->Tail = NULL;
  return 1;
} 

void Display(LIST *head)
{
  while(head != NULL)
  {
    if(head->T.Id == TOK_NUM)
      printf("%f", head->T.Num);
    else
      printf("%c", head->T.Op);
    head = head->Next;
  }
  printf("\n");
} 

int Push(STACK *S, TOK newData)
{
  LIST *newEl;
  newEl = malloc(sizeof(LIST));
  if(newEl == NULL)
  {
    printf("Error");
    return 0;
  }
    newEl->T = newData;
    newEl->Next = S->Top;
    S->Top = newEl;
    return 1;
}
int Pop(STACK *S, TOK *oldData)
{
  LIST *L;
  if(!S->Top)
  {
    printf("Error");
    return 0;
  }
  *oldData = S->Top->T;
  L = S->Top;
  S->Top = S->Top->Next;
  free(L);
  return 1;
}
void GetStr(FILE *F, char *s, int n)
{
  int c;
  while(n-- > 1)
  {
    c = getc(F);
    if(c == '\n' || c == EOF)
      break;
    *s++ = c;
  }
  *s = 0;
}

void GetStr2(char *s)
{
  GetStr(stdin, s, 257);
}

int GetPrior(char Op)
{
  switch(Op)
  {
    case'(':
      return 0;
    case')':
      return 1;
    case'+':
    case'-':
      return 2;
    case'*':
    case'%':
    case'/':
      return 3;
    case'^':
      return 4;
    case'@':
      return 5;
    default:
      return -1;
  }

}

void DropOper(STACK *S1, STACK *S2, char Op)
{
  TOK T;
  while(S2->Top != NULL && GetPrior(S2->Top->T.Op) >= GetPrior(Op)) 
  {
    Pop(S2, &T);
    Push(S1, T);
  }
}

int Parser(QUEUE *Q, QUEUE *QRES)
{
  STACK S1 = {NULL};
  STACK S2 = {NULL}; 
  TOK T;
  while(Get(Q, &T))
  {  
    if(T.Id == TOK_NUM)
      Push(&S1, T);
    else if(T.Id == TOK_OP)
    {
      if(T.Op != '(')
        DropOper(&S1, &S2, T.Op);
      if(T.Op != ')')
        Push(&S2, T);
      else
        Pop(&S2, &T);
    }
  }
// Pop(&S2, &T);
// Push(&S1, T);
  while(S1.Top != NULL)
  {
    Pop(&S1, &T);
    Push(&S2, T);
  }
  while(S2.Top != NULL)
  {
    Pop(&S2, &T);
    Put(QRES, T);
  }
  return 1;
}

int Parser2(QUEUE *Q, QUEUE *QRES)
{
 STATEID S = ST_WAIT_NUM;
 STACK S1 = {NULL};
 STACK S2 = {NULL};
 TOK T;
 while(S != ST_END)
 {
   switch(S)
   {
     case ST_WAIT_NUM:
       Get(Q, &T);
       if(T.Id == TOK_NUM)
       {
         Push(&S1, T);
         S = ST_WAIT_OP;
         break;
       }
       else if(T.Op == '(')
         Push(&S2, T);
       else if(T.Op == '-')
       {
         T.Op = '@';
         Push(&S2, T);
       }
       else
       S = ST_ERROR;
     break;
     case ST_WAIT_OP:
       if(Get(Q, &T) == 0)
       {
         S = ST_FINISH;
         break;
       }
       if(T.Id != TOK_OP)
       {
         S = ST_ERROR;
         break;
       }
       if(T.Op != ')')
       {
         DropOper(&S1, &S2, T.Op);
         Push(&S2, T);
         S = ST_WAIT_NUM;
         break;
       }
       else
       {
         DropOper(&S1, &S2, ')');
         Pop(&S2, &T);
         if(T.Op != '(')
           S = ST_ERROR;
         else
           S = ST_WAIT_OP;
       }
     break;
     case ST_FINISH:
       DropOper(&S1, &S2, ')');
       if(S2.Top != NULL)
         S = ST_ERROR;
       else 
         S = ST_END;
     break;
     case ST_ERROR:
       printf("Error in this place:");
       Display(Q->Head);
       free(&S1);
       free(&S2);
       free(Q);
       free(QRES);
       return 0;
   }
  }
  while(Pop(&S1, &T))
    Push(&S2, T);
  while(Pop(&S2, &T))
    Put(QRES, T);
  return 1;
}