#include <stdlib.h>
#include <stdio.h>
#include "lib.h"

int main()
{
    sc_memoryInit ();
    sc_memorySet(5, 10);
    printMas();
}
