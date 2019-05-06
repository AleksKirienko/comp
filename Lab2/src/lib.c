#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include "lib3.h"
#include "lib4.h"
#include "lib5.h"



#define N 100
int A[N];
int registr;
void printMas() {
    for (int i = 0; i < N; i++)
    {
        mt_gotoXY(i/10 + 2, (i % 10)*6+2 );
        printf("0x%x ", A[i]);
    }
}

int sc_regSet (int registor, int value)
{
	if (registor > 0 && registor < 6)
	{
		if (value == 1)
		{
			registr |= (1 << (registor - 1));
			return 0;
		}
		if (value == 0)
		{
			registr &= (~(1 << (registor - 1)));
			return 0;
		}
		return -1;
	}
	else
	{
		sc_regSet(E, 1);
		return -1;
	}
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

int sc_memoryGet(int address, int* value) {
  int r=0;
  if (address < 0 || address > 99) {sc_regSet (r,M); return -1;}
    else {
        *value = A[address];
        return 1;
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

int sc_regInit(void) {
    registr = 0;
    return 1;
}

int sc_regGet (int registor,int *value)
{
	int r=0;
    if (registor >= 0 && registor <= 10) {
        *value = (registr >> (registor-1)) & 0x1;
	//printf ("%d\n",value);
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
