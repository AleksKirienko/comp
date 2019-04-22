#include "lib4.h"
#include "lib3.h"
#include "lib.h"

int bc_printA(char *str) {
    printf(ENTER_MODE);
    printf("%s",str);
    printf(EXIT_MODE);
    return 0;
}

int bc_box(int x1, int y1, int x2, int y2) {
    int i;
    mt_gotoXY(x1, y1);
    bc_printA("l");
    for (i = 0; i < y2 - 2; i++)
        bc_printA("q");
    bc_printA("k");
    for (i = 1; i <= x2 - 2; i++) {
        mt_gotoXY(x1 + i, y1);
        bc_printA("x");
        mt_gotoXY(x1 + i, y1 + y2 - 1);
        bc_printA("x");
    }
    mt_gotoXY(x1 + x2 - 1, y1);
    bc_printA("m");
    for (i = 0; i < y2 - 2; i++)
        bc_printA("q");
    bc_printA("j");
    return 0;
}

int bc_printbigchar (int big[2], int x, int y, int fgcolor, int bgcolor){
    mt_setfgcolor(fgcolor);
    mt_setbgcolor(bgcolor);
    int value;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            mt_gotoXY(x + i, y + j);
            value= big[0] >> (i*8+j) & 0x1;
            if(value == 1)
                bc_printA("a");
            else
                bc_printA(" ");
        }
    }
    for (int i = 4; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            mt_gotoXY(x + i, y + j);
            value= big[1] >> (i*8+j) & 0x1;
            if(value == 1)
                bc_printA("a");
            else
                bc_printA(" ");
        }
    }
    return 1;
}

int bc_setbigcharpos (int *big, int x, int y, int value){
    if (x < 0 || x > 7 || y < 0 || y > 7 || value > 1 || value < 0) return  -1;
    int index = 0;
    if (x > 3) index = 1;
    if (value == 1){
        big[index] |= 1 << (x * 8 + y);
        return 0;
    }
    else if (value == 0){
        big[index] &= ~(1 << (x * 8 + y));
        return 0;
    }
    return -1;
}

int bc_getbigcharpos(int *big, int x, int y, int *value)
{
    if (x < 1 || x > 8 || y < 1 || y > 8)
        return -1;
    int index = 0;
    if (x > 3) index = 1;
    *value = ((big[index] >> (x * 8)) >> y) & 1;
    return 0;
}

int bc_bigcharwrite(int fd, int *big, int count)
{
    write(fd, big, sizeof(count) * 2 * count);
    close(fd);
    return 0;
}

int bc_bigcharread(int fd, int * big, int need_count, int *count) {
    (*count) = read(fd, big, sizeof(need_count) * 2 * need_count) / 8;
    if ((*count) == 0)
        return -1;
    close(fd);
    return 0;
}
void bc_setbig(int *big, char value) {
    switch (value) {
        case '+':
            big[0] = 2115508224;
            big[1] = 1579134;
            break;
        case '-':
            big[0] = 2113929216;
            big[1] = 126;
            break;
        case 0:
            big[0] = 2172731964;
            big[1] = 1010991489;
            break;
        case 1:
            big[0] = 269752336;
            big[1] = 2081427472;
            break;
        case 2:
            big[0] = 541213244;
            big[1] = 2114193424;
            break;
        case 3:
            big[0] = 809517628;
            big[1] = 1010974784;
            break;
        case 4:
            big[0] = 606613536;
            big[1] = 1881177634;
            break;
        case 5:
            big[0] = 1040319102;
            big[1] = 1044398144;
            break;
        case 6:
            big[0] = 1040335420;
            big[1] = 1010975298;
            break;
        case 7:
            big[0] = 541081726;
            big[1] = 134744080;
            break;
        case 8:
            big[0] = 1010975292;
            big[1] = 1010975298;
            break;
        case 9:
            big[0] = 1111638588;
            big[1] = 1010974844;
            break;
        case 'A':
            big[0] = 606348312;
            big[1] = 1111638654;
            break;
        case 'B':
            big[0] = 1044529726;
            big[1] = 1044529730;
            break;
        case 'C':
            big[0] = 37896764;
            big[1] = 1010975234;
            break;
        case 'D':
            big[0] = 1111638590;
            big[1] = 1044529730;
            break;
        case 'E':
            big[0] = 2114060926;
            big[1] = 2114060802;
            break;
        case 'F':
            big[0] = 2114060926;
            big[1] = 33686018;
            break;
        default:
            big[0] = 0;
            big[1] = 0;
            break;
    }
}