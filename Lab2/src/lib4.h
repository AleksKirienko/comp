#ifndef LIB4_H
#define LIB4_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ENTER_MODE "\E(0"
#define EXIT_MODE "\E(B"

int big[2];

int bc_printA (char * str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar (int big[2], int x, int y, int fgcolor, int bgcolor);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_getbigcharpos(int *big, int x, int y, int *value);
int bc_bigcharwrite(int fd, int *big, int count);
int bc_bigcharread(int fd, int *big, int need_count, int *count);

void bc_setbig(int *big, char value);

#endif