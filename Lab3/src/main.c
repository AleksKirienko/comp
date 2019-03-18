#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib.h"
#include "../../Lab2/src/lib.h"

int main()
{
    int rows, cols, color=6;
    mt_clrscr();
    mt_gotoXY(10, 7);
    mt_getscreensize(&rows, &cols);
    printf("\nrows = %d\ncols = %d\n",rows, cols);
    mt_setfgcolor (color);

}