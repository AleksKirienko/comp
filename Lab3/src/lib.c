#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "lib.h"
#include "../../Lab2/src/lib.h"
struct WinSize
{
    unsigned short ws_row;
    unsigned short ws_cols;
} ws;
int mt_clrscr(void)
{
    printf("\E[H\E[J");
    return 0;
}
int mt_gotoXY (int x, int y)
{
    printf("\E[%d;%dH", x, y);
    return 0;
}
int mt_getscreensize (int *rows, int *cols)
{
    if (!ioctl(1, TIOCGWINSZ, &ws))
    {
        (*rows) = ws.ws_row;
        (*cols) = ws.ws_cols;
        return 0;
    } else {
        printf("Error getting size");
        return -1;
    }
}
int mt_setfgcolor (int colors)
{
    printf("\E[3%dm", colors);
    return 0;
}