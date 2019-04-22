#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include "lib3.h"
#include "lib4.h"

#define O 10
#define T 11
#define M 12
#define P 13
#define E 14

#define N 100
int A[N];
int flag;

void printMas() {
    for (int i = 0; i < N; i++)
    {
        mt_gotoXY(i/10 + 2, (i % 10)*6+2 );
        printf("0x%x ", A[i]);
    }
}

int sc_regSet (int registr, int value)
{
  int r=0;
    if (value >= O && value <= E)
    {
        registr |= value;
        printf ("%d\n",registr);
        return 1;
    }
    else {sc_regSet (r,E); return -1;}
}

int sc_memoryInit() {
    int i;
    for (i = 0; i < N; i++) {
        A[i] = 0;
    }
    return 1;
}

int sc_memorySet(int address, int value) {
  int r=0;
  if (address < 0 || address > 99) {sc_regSet (r,M); return -1;}
    else {
        A[address] = value;
        return 1;
    }
}

int sc_memoryGet(int address, int value) {
  int r=0;
  if (address < 0 || address > 99) {sc_regSet (r,M); return -1;}
    else {
        value = A[address];
        return value;
    }
}

int sc_memorySave(FILE *filename) {
    fwrite(A, sizeof(A), 1, filename);
    return 1;
}

int sc_memoryLoad(FILE *filename) {
    fread(A, sizeof(A), 1, filename);
    return 1;
}

int sc_regInit(int registr) {
    registr = 0;
    return 1;
}


int sc_regGet (int registr,int value)
{
  int r=0;
    if (registr >= 0 && registr <= 10) {
        value = (registr >> (value-1)) & 0x1;
	 printf ("%d\n",value);
	return 1;
    }
    else {sc_regSet (r,E); return -1;}
}
int sc_commandEncode(int command, int operand, int *value)
{
  int r=0;
    if (command == 10 || command == 11 || command == 20 || command == 21 || (command > 29 && command < 34) || (command > 39 && command < 44) || (command > 50 && command < 77)) {
        if (operand < 128)
	 {
	   *value = command << 7;
	   
	   *value|= operand;
           
            printf ("%d",*value);
		
            printf ("\n");
            return 1;
        }
    }
    sc_regSet (r,E); return -1;
}
int sc_commandDecode(int value, int *command, int *operand)
{
int r = 0;
  *command = (value >> 7);
if (*command == 10 || *command == 11 || *command == 20 || *command == 21 || (*command > 29 && *command < 34) || (*command > 39 && *command < 44) || (*command > 50 && *command < 77)) {
  *operand = value&(~(value << 7));
    }
else {sc_regSet (r,E); return -1;}
    printf ("%d\n",*operand);
    printf ("%d\n",*command);
    return 1;
	
}
