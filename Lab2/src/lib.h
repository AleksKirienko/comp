#ifndef LIB_H
#define LIB_H

#define O 1
#define T 2
#define M 3
#define P 4
#define E 5

extern int registr;

void printMas();
int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(FILE* filename);
int sc_memoryLoad(FILE* filename);
int sc_regInit(void);
int sc_regSet(int registor,int value);
int sc_regGet(int registor,int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);

#endif
