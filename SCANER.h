#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

typedef enum
{
  TOK_NUM,
  TOK_OP
}TOKID;
typedef enum
{
 ST_WAIT_NUM,
 ST_WAIT_OP,
 ST_FINISH,
 ST_END,
 ST_ERROR
}STATEID;
typedef struct       
{
  TOKID Id;
  double Num;
  char Op;
}TOK;

typedef struct tagLIST LIST;
struct tagLIST
{
   TOK T;
   LIST *Next;
};
typedef struct
{
  LIST *Head;
  LIST *Tail;
}QUEUE;

typedef struct
{
  LIST *Top;
}STACK;

 int Put(QUEUE *Q, TOK newdata);
 int Get(QUEUE *Q, TOK *oldData);
 void Display(LIST *head);
 int Push(STACK *S, TOK newData);
 int Pop(STACK *S, TOK *oldData);
 void GetStr(FILE *F, char *s, int n);
 void GetStr2(char *s);
 int Scanner(QUEUE *Q, char *s);
 double Eval(QUEUE *Q, STACK *S);
 int Parser(QUEUE *Q, QUEUE *QRES);
 int Parser2(QUEUE *Q, QUEUE *QRES);


