#include <stdio.h>
#include "lib.h"
#include "lib3.h"
#include "lib4.h"
#include "lib5.h"

int CU (void)
{
    int value, command, operand;
    sc_memoryGet(address, &value);
    if (sc_commandDecode( value, &command, &operand) == -1)
    {
        sc_regSet(T, 1);
        mt_gotoXY(11, 76);
        mt_setbgcolor(4);
        printf("T");
        mt_gotoXY(25, 1);
        return -1;
    }
    if (command >= 0x30 && command <= 33)
        return ALU(command, operand);
    switch (command)
    {
        case 0x10:
            break;
        case 0x11:
            if (sc_memoryGet(operand, &value == -1){
                sc_regSet(M, 1);
                return -1;
            }
            printf("%d", value);
            break;
        case 0x20:
            if (sc_memoryGet(operand, &value == -1){
                sc_regSet(M, 1);
                return -1;
            }
            valacc = value;
            mt_gotoXY(2, 67);
            if (valacc < 32768) printf ("+");
            else if (valacc >= 0) printf (" ");
            printf("%x   ", valacc);
            break;
        case 0x21:
            value = valacc;
            if (sc_memorySet(operand, valacc) == -1){
                sc_regSet(M, 1);
                return -1;
            }
            mt_gotoXY((operand % 10) * 6 + 2, operand / 10 + 2);
            mt_setbgcolor(9);
            if (valacc<32768)  printf("+");
            else printf(" ");
            printf("%x    ", valacc);

            itoa(value, A);
            print (value, A);


            break;
        case 0x40:
            if (sc_memoryGet(operand, &value == -1){
                sc_regSet(M, 1);
                return -1;
            }
            break;
        case 0x41:
            break;
        case 0x42:
            break;
        case 0x43:
            break;
        case 0x59:
            break;
        case 0x66:
            break;
    }

    return 0;
}
int ALU(int command, int operand)
{
    if (sc_memoryGet(address, &value) == -1)
    {
        sc_regSet(M, 1);
        mt_gotoXY(11, 74);
        mt_setbgcolor(4);
        printf("M");
        mt_gotoXY(25, 1);
        return -1;
    }
    switch (command)
    {
        case 0x30:
            break;
        case 0x31:
            break;
        case 0x32:
            break;
        case 0x33:
            break;
    }

}