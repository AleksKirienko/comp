#include <stdio.h>
#include "lib.h"
#include "lib3.h"
#include "lib4.h"
#include "lib5.h"

int address = 0;
int x = 2, y = 2;
int rk_mytermsave ()
{
	struct termios term;
	if (tcgetattr(0, &term) == -1) return -1;
	FILE *f = fopen ("save.out", "wb");
	if (!f) return -1;
	fwrite (&term, sizeof(term),1, f);
	fclose (f);
	return 0;
	
}
int rk_mytermrestore ()
{
	struct termios term;
	FILE *f = fopen ("load.in", "rb");
	if (!f) return -1;
	fread (&term, sizeof(term),1, f);
	if (tcsetattr(0, TCSADRAIN, &term) == -1) return -1;
	fclose (f);
	return 0;
}
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
    struct termios term;
    if (tcgetattr(0, &term) == -1) return -1;
    regime == 1 ? term.c_lflag |= ICANON : term.c_lflag &= ~ICANON;
    sigint == 1 ? term.c_lflag |= ISIG : term.c_lflag &= ~ISIG;
    echo == 1 ? term.c_lflag |= ECHO : term.c_lflag &= ~ECHO;

    term.c_cc[VTIME] = vtime;
    term.c_cc[VMIN] = vmin;
    if (tcsetattr(0, TCSADRAIN, &term) == -1) return -1;
    return 0;
}
int read_key(int key)
{
	int value;
	switch (key)
	{
		case 1: 
		{
			if (address % 10 == 9) return -1;
			mt_setbgcolor (0);
			x+=7;
			address++;
			sc_memoryGet(address, &value);
			mt_setbgcolor (4);
			mt_gotoXY(x, y);
			printf("%x",value);
			break;	
		}
		case 2: 
		{
			if (address % 10 == 0) return -1;
			mt_setbgcolor (0);
			x-=7;
			address--;
			sc_memoryGet(address, &value);
			mt_setbgcolor (4);
			mt_gotoXY(x, y);
			printf("%x",value);
			break;	
		}
		case 3: 
		{
			if (address / 10 == 9) return -1;
			mt_setbgcolor (0);
			y--;
			address-=10;
			sc_memoryGet(address, &value);
			mt_setbgcolor (4);
			mt_gotoXY(x, y);
			printf("%x",value);
			break;	
		}
		case 4: 
		{
			if (address / 10 == 0) return -1;
			mt_setbgcolor (0);
			y++;
			address+=10;
			sc_memoryGet(address, &value);
			mt_setbgcolor (4);
			mt_gotoXY(x, y);
			printf("%x",value);
			break;	
		}
	}
}
