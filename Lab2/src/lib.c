#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include "lib3.h"
#include "lib4.h"
#include "lib5.h"
#include "cu.h"

#define N 100
int A[N];
int registr;
void printMas() {
    for (int i = 0; i < N; i++)
    {
        mt_gotoXY(i/10 + 2, (i % 10)*6+2 );
	    printf("      ");
	    mt_gotoXY(i/10 + 2, (i % 10)*6+2 );
        if (A[i]<32768)  printf("+");
        printf("%x", A[i]);
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
}

int sc_memoryInit() {
    int i;
    for (i = 0; i < N; i++) {
        A[i] = 0;
    }
    return 1;
}

int sc_memorySet(int address, int value) {
  if (address < 0 || address > 99 || value < 0 || value > 32767) 
	{
		sc_regSet(M, 1);
   		mt_gotoXY(11, 74);
    	mt_setbgcolor(4);
    	printf("M");
   		mt_gotoXY(25, 1);
		mt_setbgcolor (9);
		return -1;
	}
    else {
        A[address] = value;
        return 1;
    }
}

int sc_memoryGet(int address, int* value) {
  if (address < 0 || address > 99) {
		sc_regSet(M, 1);
   		mt_gotoXY(11, 74);
    	mt_setbgcolor(4);
    	printf("M");
   		mt_gotoXY(25, 1);
		mt_setbgcolor (9);
		return -1;
	}
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
    if (registor >= 0 && registor <= 10)
        *value = (registr >> (registor-1)) & 0x1;
	return 1;
  
}
int sc_commandEncode(int command, int operand, int *value)
{
	*value = command << 7;
	*value|= operand;
    if (command == 0x10 || command == 0x11 || command == 0x20 || command == 0x21 || (command > 0x29 && command < 0x34) || (command > 0x39 && command < 0x44) || (command > 0x50 && command < 77))
	{
        if (operand < 128) return 1;

    }
		return -1;
}
int sc_commandDecode(int value, int *command, int *operand)
{
  	*command = (value >> 7);
	*operand = value & 0x7F;
	if (*command == 0x10 || *command == 0x11 || *command == 0x20 || *command == 0x21 || (*command > 0x29 && *command < 0x34) || (*command > 0x39 && *command < 0x44) || (*command > 0x50 && *command < 0x77))
	{
  		return 1;
    }
	else 
	{
		
		return -1;
	}
   // printf ("%d\n",*operand);
   // printf ("%d\n",*command);
	
}
