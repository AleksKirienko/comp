#include <stdlib.h>
#include <stdio.h>

#define mask 0xF
#define mask1 0x01
#define mask2 0x10
#define N 100
int A[N];
int flag;

void printMas() {
    for (int i = 0; i < N; ++i)
        printf("%d ", A[i]);
    printf("\n");
}

int sc_memoryInit() {
    int i;
    for (i = 0; i < N; i++) {
        A[i] = 0;
    }
    return 1;
}

int sc_memorySet(int address, int value) {
    if (address < 0 || address > 99) return -1;
    else {
        A[address] = value;
        return 1;
    }
}

int sc_memoryGet(int address, int *value) {
    if (address < 0 || address > 99) return -1;
    else {
        value = &A[address];
        return 1;
    }
}

int sc_memorySave(FILE *filename) {
    fwrite(A, 1, sizeof(A), filename);
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

/*int sc_regSet (int registr, int value)
{
if (registr >= mask1 && registr <= mask2)
{
//registr = registr|(1 << (value - 1));
return 1;
}
else return -1;
}
int sc_regGet (int registr, int * value)
{
if (registr >= mask1 && registr <= mask2)
{
//flag = (registr >> (value-1)) & 0x1;
return 1;
}
else return -1;
}*/
int sc_commandEncode(int command, int operand, int *value) {
    if (command == 10 || command == 11 || command == 20 || command == 21 || command > 29 || command < 34 ||
        command > 39 || command < 44 || command > 50 || command < 77) {
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

            return 1;

        }
    }
    return -1;
}
/*int sc_commandDecode(int value, int * command, int * operand)
{
	return -1;
}
*/