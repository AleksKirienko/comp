#include <stdio.h>
#include "lib.h"
#include "lib3.h"
#include "lib4.h"
#include "lib5.h"

int CU (char A[])
{
    int value, command, operand;
	mt_setbgcolor(9);
	mt_gotoXY(30, 1);
    printf("          ");
	mt_gotoXY(30, 1);
    sc_memoryGet(address, &value);
    if (sc_commandDecode( value, &command, &operand) == -1)
    {
        sc_regSet(E, 1);
        mt_gotoXY(11, 70);
        mt_setbgcolor(4);
        printf("E");
        mt_gotoXY(25, 1);
        return -1;
    }
    if (command >= 0x30 && command <= 0x33)
        return ALU(command, operand);
    switch (command)
    {
        case 0x10:
            alarm(0);
            rk_mytermregime(1, 1, 1, 1, 1);
            scanf("%d", &value);
            rk_mytermregime(0, 0, 1, 0, 1);
            if (sc_memorySet(operand, value) == -1){
                sc_regSet(M, 1);
                return -1;
            }
            mt_gotoXY(operand/10 + 2, (operand % 10)*6+2 );
			printf("      ");
			mt_gotoXY(operand/10 + 2, (operand % 10)*6+2 );
            mt_setbgcolor(9);
            if (value<32768)  printf("+");
            else printf(" ");
            printf("%x    ", value);
            alarm(1);
            break;
        case 0x11:
            if (sc_memoryGet(operand, &value) == -1){
                sc_regSet(M, 1);
                return -1;
            }
			mt_gotoXY(30, 1);
            printf("%d", value);
            break;
        case 0x20:
            if (sc_memoryGet(operand, &value) == -1){
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
            if (sc_memorySet(operand, valacc) == -1){
                sc_regSet(M, 1);
                return -1;
            }
            mt_gotoXY((operand % 10) * 6 + 2, operand / 10 + 2);
            mt_setbgcolor(9);
            if (valacc<32768)  printf("+");
            else printf(" ");
            printf("%x    ", valacc);
            break;
        case 0x40:
            if (sc_memoryGet(operand, &value) == -1){
                sc_regSet(M, 1);
                return -1;
            }
            mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
			printf("      ");
			mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
            address = operand - 1;
            mt_setbgcolor(9);
            if (value<32768)  printf("+");
            else printf(" ");
            printf("%x", value);
            break;
        case 0x41:
            if (sc_memoryGet(operand, &value) == -1){
                sc_regSet(M, 1);
                return -1;
            }
            if(valacc < 0) {
				sc_memoryGet(address, &value);
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                mt_setbgcolor(9);
                if (value < 32768) printf("+");
                else printf(" ");
                printf("%x", value);
				address = operand - 1;
            }
            break;
        case 0x42:
            if (sc_memoryGet(operand, &value) == -1){
                sc_regSet(M, 1);
                return -1;
            }
            if(valacc == 0) {
                sc_memoryGet(address, &value);
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                mt_setbgcolor(9);
                if (value < 32768) printf("+");
                else printf(" ");
                printf("%x", value);
				address = operand - 1;
            }
            break;
        case 0x43:
            return -1;
        case 0x59:
            if (sc_memoryGet(operand, &value) == -1){
                sc_regSet(M, 1);
                return -1;
            }
            if (valacc % 2 != 0){
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                mt_setbgcolor(9);
                if (value < 32768) printf("+");
                else printf(" ");
                printf("%x", value);
				address = operand - 1;
            }
            break;
        case 0x66:
            if (sc_memoryGet(operand, &value) == -1){
                sc_regSet(M, 1);
                return -1;
            }
            int value2;
            if (sc_memoryGet(valacc, &value2) == -1){
                sc_regSet(M, 1);
                return -1;
            }
            value-=value2;
            valacc=value;

            mt_gotoXY(2, 67);
            if (valacc < 32768) printf ("+");
            else printf (" ");
            printf("%x   ", valacc);
            break;
        default:
            return -1;
    }
    return 0;
}

int ALU(int command, int operand)
{
    int value;
    if (sc_memoryGet(operand, &value) == -1)
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
            valacc+=value;
            if(valacc > 32766 || valacc < -32766){
				sc_regSet(P, 1);
       			mt_gotoXY(11, 72);
       			mt_setbgcolor(4);
        		printf("P");
        		mt_gotoXY(25, 1);
                return -1;
            }
            break;
        case 0x31:
            valacc -= value;
            if(valacc > 32766 || valacc < -32766){
				sc_regSet(P, 1);
       			mt_gotoXY(11, 72);
       			mt_setbgcolor(4);
        		printf("P");
        		mt_gotoXY(25, 1);
                sc_regSet(P, 1);
                return -1;
            }
            break;
        case 0x32:
            if(value == 0) {
				sc_regSet(O, 1);
                mt_gotoXY(11, 68);
                mt_setbgcolor(4);
                printf("O");
                mt_gotoXY(25, 1);
                return -1;
            }
            valacc/=value;
            if(valacc > 32766 || valacc < -32766){
				sc_regSet(P, 1);
       			mt_gotoXY(11, 72);
       			mt_setbgcolor(4);
        		printf("P");
        		mt_gotoXY(25, 1);
                sc_regSet(P, 1);
                return -1;
            }
            break;
        case 0x33:
            valacc*=value;
            if(valacc > 32766 || valacc < -32766){
				sc_regSet(P, 1);
       			mt_gotoXY(11, 72);
       			mt_setbgcolor(4);
        		printf("P");
        		mt_gotoXY(25, 1);
                sc_regSet(P, 1);
                return -1;
            }
            break;
        default:
            return -1;
    }
    mt_gotoXY(2, 67);
    if (valacc < 32768) 
		if (valacc >= 0)
			printf ("+%x    ", valacc);
		else
			printf("-%x    ",valacc * -1);
    else printf (" %x     ",valacc);
    return 0;
}
