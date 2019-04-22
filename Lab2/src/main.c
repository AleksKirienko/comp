#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include "lib3.h"
#include "lib4.h"
#include "lib5.h"

int main()
{
    int fd = open("src/Bigchars", O_WRONLY);
    mt_clrscr();
    sc_memoryInit ();
    //int r=0;

    sc_memorySet(15, 9);
    bc_box(1, 1, 12, 63);
    mt_gotoXY(2, 0);
    printMas();
    mt_gotoXY(1, 28);
    printf("Memory");

    bc_box(1, 64, 3, 20);
    mt_gotoXY(1, 67);
    printf("Accumulator");

    bc_box(4, 64, 3, 20);
    mt_gotoXY(4, 65);
    printf("InstructionCounter");

    bc_box(7, 64, 3, 20);
    mt_gotoXY(7, 70);
    printf("Operation");

    bc_box(10, 64, 3, 20);
    mt_gotoXY(10, 70);
    printf("Flags");
    mt_gotoXY(11, 68);
    printf("O E V M");

    bc_box(13, 44, 10, 20);
    mt_gotoXY(13, 50);
    printf("Keys");
    mt_gotoXY(14, 45);

    printf("L  - load");
    mt_gotoXY(15, 45);
    printf("S  - save ");

    bc_box(13, 1, 10, 42);
    bc_setbig(big, '+');
    bc_setbigcharpos (big, 4, 1, 0);
    bc_setbigcharpos (big, 1, 1, 1);

    bc_printbigchar (big,14, 2, 7, 2);
    bc_setbig(big, 0);
    bc_printbigchar (big,14, 10, 7, 2);
    bc_setbig(big, 0);
    bc_printbigchar (big,14, 18, 7, 2);
    bc_setbig(big, 0);
    bc_printbigchar (big,14, 26, 7, 2);
    bc_setbig(big, 0);
    bc_printbigchar (big,14, 34, 7, 2);

    int B[8];
    bc_setbig(big, 1);
    B[0]=big[0];
    B[1]=big[1];
    bc_setbig(big, 2);
    B[2]=big[0];
    B[3]=big[1];

    bc_setbig(big, 3);
    B[4]=big[0];
    B[5]=big[1];

    bc_setbig(big, 4);
    B[6]=big[0];
    B[7]=big[1];
    bc_bigcharwrite(fd, B, 4);
    //close (fd);
    int fd2 = open("src/Bigchars", O_RDONLY);
    for (int i=0; i<8; i++){
        B[i]= 0;
    }
    int amount;
    bc_bigcharread(fd2, B, 8, &amount);
    mt_gotoXY(30, 0);
    int value5;
    bc_setbig(big, 0);
    bc_getbigcharpos(big, 1, 1, &value5);
    printf("%d %d %d",B[7], amount, value5);

}
