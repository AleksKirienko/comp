#ifndef LIB_H
#define LIB_H

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int* value);
int sc_memorySave(char * filename);
int sc_memoryLoad(char * filename);
int sc_regInit();
int sc_regSet(int registr, int value);
int sc_regGet(int registr, int * value);
int sc_commandEncode(int command, int operand, int * value);
int sc_commandDecode(int value, int * command, int * operand);

#endif
