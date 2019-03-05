#include <stdlib.h>
#include <stdio.h>

#define O 10
#define T 11
#define M 12
#define P 13
#define E 14

#define N 100
int A[N];
int flag;
int registr;

void printMas() {
    for (int i = 0; i < N; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int sc_regSet (int value)
{
    if (value >= O && value <= E)
    {
        registr = value;
        printf ("%d\n",registr);
        return 1;
    }
    else {sc_regSet (E); return -1;}
}

int sc_memoryInit() {
    int i;
    for (i = 0; i < N; i++) {
        A[i] = 0;
    }
    return 1;
}

int sc_memorySet(int address, int value) {
  if (address < 0 || address > 99) {sc_regSet (M); return -1;}
    else {
        A[address] = value;
        return 1;
    }
}

int sc_memoryGet(int address, int value) {
    if (address < 0 || address > 99) {sc_regSet (M); return -1;}
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

int sc_regInit() {
    registr = 0;
    return 1;
}


int sc_regGet (int value)
{
    if (value >= O && value <= E) {
        value = registr;
	 printf ("%d\n",registr);
	return 1;
    }
    else {sc_regSet (E); return -1;}
}
int sc_commandEncode(int command, int operand, int *value)
{
    if (command == 10 || command == 11 || command == 20 || command == 21 || (command > 29 && command < 34) ||
            (command > 39 && command < 44) || (command > 50 && command < 77)) {
        if (operand / 10 < 8) {
            value[0] = 0;

            value[3] = (command / 10) % 2;
            value[2] = ((command / 10) / 2) % 2;
            value[1] = (((command / 10) / 2) / 2) % 2;
            value[7] = (command % 10) % 2;
            value[6] = ((command % 10) / 2) % 2;
            value[5] = (((command % 10) / 2) / 2) % 2;
            value[4] = ((((command % 10) / 2) / 2) / 2) % 2;

            value[10] = (operand / 10) % 2;
            value[9] = ((operand / 10) / 2) % 2;
            value[8] = (((operand / 10) / 2) / 2) % 2;
            value[14] = (operand % 10) % 2;
            value[13] = ((operand % 10) / 2) % 2;
            value[12] = (((operand % 10) / 2) / 2) % 2;
            value[11] = ((((operand % 10) / 2) / 2) / 2) % 2;

            for (int i = 0; i<15;i++)
            {
                printf ("%d",value[i]);
            }
            printf ("\n");
            return 1;
        }
    }
    sc_regSet (E); return -1;
}
int sc_commandDecode(int *value, int command, int operand)
{
    for (int i = 0; i<15; i++)
    {
        if ((value[i] != 0) && (value[i] != 1)) {sc_regSet (E); return -1;}
    }
	command = (value[1]*4 + value [2]*2 +value [3])*10 + value[4]*8+ value[5]*4+value[6]*2+value[7];
    printf ("%d ",command);
    operand = (value[8]*4 + value [9]*2 +value [10])*10 + value[11]*8+ value[12]*4+value[13]*2+value[14];
    printf ("%d\n",operand);
    return 1;
}
