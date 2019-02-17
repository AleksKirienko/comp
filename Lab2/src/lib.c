#include <stdio.h>
#include "lib.h"
#define mask 0xF
const int N=100;
int A[N];
int flag;
int sc_memoryInit ()
{
  int i;
  for (i=0;i<N;i++)
    A[i]=0;
}
int sc_memorySet (int address, int value)
{
  if (address < 0 || address>99) return -1;
  else
    {
      A[address] = value;
      return 1;
    }
}
int sc_memoryGet (int address, int* value)
{
 if (address < 0 || address>99) return -1;
 else
   {
     value = A[address];
     return 1;
   }
}
int sc_memorySave (char * filename)
{
  fwrite(A , 1 , sizeof(A) , filename); 
}
int sc_memoryLoad (char * filename)
{
  fread(A, sizeof(A), 1, filename); 
}
int sc_regInit ()
{
  flag = 0;
}
