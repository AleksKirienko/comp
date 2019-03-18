#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib.h"
#include "../../Lab2/src/lib.h"

int main()
{
    int rows, cols;
    mt_clrscr();
    mt_gotoXY(10, 7);
    mt_getscreensize(&rows, &cols);
    mt_setfgcolor(1);
    mt_setbgcolor(4);
    printf("\nrows = %d\ncols = %d\n",rows, cols);
}