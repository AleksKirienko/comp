#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

int main()
{
    int c = sc_memoryInit ();
    printf ("sc_memoryInit finish with code: %d\n", c);

    c = sc_memorySet(5, 10);
    printf ("sc_memorySet finish with code: %d\n", c);
    printMas();

    int value = 0;
    value = sc_memoryGet(5, value);
    if (value == -1) printf ("sc_memoryGet finish with code: %d\n", c);
    else printf ("sc_memoryGet finish with code: 1\n");
    if (value !=-1) printf ("Value = %d\n", value);

    FILE* file = fopen ("Text.dat", "wb");
    c = sc_memorySave(file);
    printf ("sc_memorySave finish with code: %d\n", c);
    fclose (file);

    file = fopen ("Text.dat", "rb");
    c = sc_memoryLoad(file);
    printf ("sc_memoryLoad finish with code: %d\n", c);
    fclose (file);
    printMas();

    c = sc_regInit();
    printf ("sc_regInit finish with code: %d\n", c);

    c = sc_regSet(10);
    printf ("sc_regSet finish with code: %d\n", c);

    c = sc_regGet(10);
    printf ("sc_regGet finish with code: %d\n", c);

    int value1[15]={0};
    c = sc_commandEncode(33, 59, value1);
    printf ("sc_commandEncode finish with code: %d\n", c);

    int command=0, operand=0;
    c = sc_commandDecode(value1, command, operand);
    printf ("sc_commandEncode finish with code: %d\n", c);
}
