#include <stdio.h>
#include "lib.h"
#include "lib3.h"
#include "lib4.h"
#include "lib5.h"

int address = 0;
int x = 2, y = 2;
int Instr = 0;
void print (int value, char* A)
{
	if (value == 0)
    		{
		bc_setbig(big, '+');
		bc_printbigchar (big,14, 2, 7, 2);
    		bc_setbig(big, '0');
    		bc_printbigchar (big,14, 10, 7, 2);
    		bc_setbig(big, '0');
    		bc_printbigchar (big,14, 18, 7, 2);
    		bc_setbig(big, '0');
   		bc_printbigchar (big,14, 26, 7, 2);
    		bc_setbig(big, '0');
    		bc_printbigchar (big,14, 34, 7, 2);
    	
		}
	else 
	{
		bc_setbig(big, ' ');
		bc_printbigchar (big,14, 2, 7, 2);
		if (A[3] <= '9' && A[3]>='0')
    		{
			bc_setbig(big, A[0]);
    			bc_printbigchar (big,14, 10, 7, 2);
    			bc_setbig(big, A[1]);
    			bc_printbigchar (big,14, 18, 7, 2);
    			bc_setbig(big, A[2]);
    			bc_printbigchar (big,14, 26, 7, 2);
    			bc_setbig(big, A[3]);
    			bc_printbigchar (big,14, 34, 7, 2);
		}
		else if (A[2] <= '9' && A[2]>='0')
    		{
			bc_setbig(big, A[3]);
    			bc_printbigchar (big,14, 10, 7, 2);
    			bc_setbig(big, A[0]);
    			bc_printbigchar (big,14, 18, 7, 2);
    			bc_setbig(big, A[1]);
    			bc_printbigchar (big,14, 26, 7, 2);
    			bc_setbig(big, A[2]);
    			bc_printbigchar (big,14, 34, 7, 2);
		}
		else if (A[1] <= '9' && A[1]>='0')
    		{
			bc_setbig(big, A[2]);
    			bc_printbigchar (big,14, 10, 7, 2);
    			bc_setbig(big, A[3]);
    			bc_printbigchar (big,14, 18, 7, 2);
    			bc_setbig(big, A[0]);
    			bc_printbigchar (big,14, 26, 7, 2);
    			bc_setbig(big, A[1]);
    			bc_printbigchar (big,14, 34, 7, 2);
		}
		else if (A[0] <= '9' && A[0]>='0')
    		{
			bc_setbig(big, A[3]);
    			bc_printbigchar (big,14, 10, 7, 2);
    			bc_setbig(big, A[2]);
    			bc_printbigchar (big,14, 18, 7, 2);
    			bc_setbig(big, A[1]);
    			bc_printbigchar (big,14, 26, 7, 2);
    			bc_setbig(big, A[0]);
    			bc_printbigchar (big,14, 34, 7, 2);
		}
	}
}
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
    //regime == 1 ? term.c_lflag |= ICANON : term.c_lflag &= ~ICANON;
    if (tcgetattr(0, &term) == -1)
        return -1;
    if (regime == 1)
        term.c_lflag |= ICANON;
    else
    if (regime == 0)
        term.c_lflag &= ~ICANON;
    else
        return -1;

    //sigint == 1 ? term.c_lflag |= ISIG : term.c_lflag &= ~ISIG;
    if (sigint == 1)
        term.c_lflag |= ISIG;
    else
    if (sigint == 0)
        term.c_lflag &= ~ISIG;
    else
        return -1;
    //echo == 1 ? term.c_lflag |= ECHO : term.c_lflag &= ~ECHO;
    if (echo == 1)
        term.c_lflag |= ECHO;
    else
    if (echo == 0)
        term.c_lflag &= ~ECHO;
    else
        return -1;

    term.c_cc[VTIME] = vtime;
    term.c_cc[VMIN] = vmin;
    if (tcsetattr(0, TCSADRAIN, &term) == -1) return -1;
    return 0;
}
int rk_readkey (enum keys *key)
{
    *key=100;
    char A[8];
    rk_mytermregime(0, 0, 1, 0, 1);

    int Count = read (0, A, 7);
    A[Count] = '\0';
    if (!strcmp(A, "\E[A"))
        *key = Up;
    else if (!strcmp(A, "\E[C"))
        *key = Right;
    else if (!strcmp(A, "\E[B"))
        *key = Down;
    else if (!strcmp(A, "\E[D"))
        *key = Left;
    else if (!strcmp(A, "\E["))
        *key= Esc;
    else if (!strcmp(A, "i"))
        *key= Reset;
    else if (!strcmp(A, "r"))
        *key= Run;
    else if (!strcmp(A, "s"))
        *key= Save;
    else if (!strcmp(A, "l"))
        *key= Load;
    else if (!strcmp(A, "\E[15~"))
        *key= F5;
    else if (!strcmp(A, "\E[17~"))
        *key= F6;

    rk_mytermregime(1, 1, 1, 1, 1);
    read_key(*key);
    printf("%s ",A);
    return 0;
}

/* reverse:  переворачиваем строку s на месте */
void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* записываем знак */
        n = -n;          /* делаем n положительным числом */
    i = 0;
    do {       /* генерируем цифры в обратном порядке */
        s[i++] = n % 10 + '0';   /* берем следующую цифру */
    } while ((n /= 10) > 0);     /* удаляем */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void printGUI (void)
{
	mt_clrscr();
    sc_memoryInit ();

    bc_box(1, 1, 12, 63);
    mt_gotoXY(2, 0);
    printMas();

    int value;
    sc_memoryGet(0, &value);
    mt_gotoXY(2, 2);
    mt_setbgcolor (4);
    printf("0x%x",value);
    mt_setbgcolor (9);
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
    printf("O E V M T");

    bc_box(13, 44, 10, 20);
    mt_gotoXY(13, 50);
    printf("Keys");
    mt_gotoXY(14, 45);

    printf("L  - load");
    mt_gotoXY(15, 45);
    printf("S  - save ");
    mt_gotoXY(16, 45);
    printf("i - Reset ");
    mt_gotoXY(17, 45);
    printf("r - Run");
    mt_gotoXY(18, 45);
    printf("Esc - escape ");
    mt_gotoXY(19, 45);
    printf("F5 - enter chars");


    bc_box(13, 1, 10, 42);
    bc_setbig(big, '+');
    bc_setbigcharpos (big, 4, 1, 0);
    bc_setbigcharpos (big, 1, 1, 1);

    bc_printbigchar (big,14, 2, 7, 2);
    bc_setbig(big, '0');
    bc_printbigchar (big,14, 10, 7, 2);
    bc_setbig(big, '0');
    bc_printbigchar (big,14, 18, 7, 2);
    bc_setbig(big, '0');
    bc_printbigchar (big,14, 26, 7, 2);
    bc_setbig(big, '0');
    bc_printbigchar (big,14, 34, 7, 2);
}

void sighandler (int signo)
{
	alarm(0);
	sc_regInit();
	sc_memoryInit();
	printGUI();
}

void shandler(int signo)
{
    int value;
    char A[4];
    int big[2];

    if (address == 99)
    {
        sc_memoryGet(address, &value);
        mt_gotoXY(x, y);
        mt_setbgcolor(9);
        printf("0x%x", value);
        x = 2;
        y = 2;
        address=0;

        sc_memoryGet(address, &value);
        mt_setbgcolor(4);
        mt_gotoXY(x, y);
        printf("0x%x", value);
    }
    if (address % 10 == 9)
    {
        sc_memoryGet(address, &value);
        mt_gotoXY(x, y);
        mt_setbgcolor(9);
        printf("0x%x", value);
        y = 2;
        x++;
        address++;
        sc_memoryGet(address, &value);
        mt_setbgcolor(4);
        mt_gotoXY(x, y);
        printf("0x%x", value);
    }
    else
     {
        sc_memoryGet(address, &value);
        mt_gotoXY(x, y);
        mt_setbgcolor(9);
        printf("0x%x", value);
        y += 6;
        address++;
        sc_memoryGet(address, &value);
        mt_setbgcolor(4);
        mt_gotoXY(x, y);
        printf("0x%x", value);
        //mt_gotoXY(23, 1);
    }
    itoa(value, A);
	print (value, A);
}

void Signal(void)
{
    int value;
    sc_regSet(T, 0);

    sc_memoryGet(address, &value);
    mt_gotoXY(x, y);
    mt_setbgcolor(9);
    printf("0x%x", value);
    x = 2;
    y = 2;
    address = 0;

    signal (SIGUSR1, sighandler);
    raise (SIGUSR1);

    Instr = 0;
    mt_gotoXY(5, 65);
    mt_setbgcolor(9);
    printf ("0x%d", Instr);
}
void Timer (void)
{
    sc_regSet(T, 1);
    struct itimerval nval, oval;
    signal (SIGALRM, shandler);

    nval.it_interval.tv_sec = 1;
    nval.it_interval.tv_usec = 1;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;

    setitimer (ITIMER_REAL, &nval, &oval);
}

int read_key(enum keys key)
{
    FILE *f;
	int value;
	char A[4];
	int big[2];
	sc_regGet (T, &value);
	if (value == 1 && key != Reset){
	    Timer();

        Instr = address;
        mt_gotoXY(5, 65);
        mt_setbgcolor(9);
        printf ("0x%d", Instr);

        mt_gotoXY(11, 76);
        mt_setbgcolor(4);
        printf("T");
        mt_gotoXY(25, 1);

        return 0;
	}
    if (value == 0) {
        switch (key) {
            case Right:

                if (address % 10 == 9) break;
                sc_memoryGet(address, &value);
                mt_gotoXY(x, y);
                mt_setbgcolor(9);
                printf("0x%x", value);
                y += 6;
                address++;
                sc_memoryGet(address, &value);
                mt_setbgcolor(4);
                mt_gotoXY(x, y);
                printf("0x%x", value);
                mt_gotoXY(23, 1);

                itoa(value, A);
                 print (value, A);

                break;
            case Left:

                if (address % 10 == 0) break;
                sc_memoryGet(address, &value);
                mt_gotoXY(x, y);
                mt_setbgcolor(9);
                printf("0x%x", value);
                y -= 6;
                address--;
                sc_memoryGet(address, &value);
                mt_setbgcolor(4);
                mt_gotoXY(x, y);
                printf("0x%x", value);
                mt_gotoXY(23, 1);

                itoa(value, A);
                 print (value, A);

                break;
            case Up:

                if (address / 10 == 0) break;
                sc_memoryGet(address, &value);
                mt_gotoXY(x, y);
                mt_setbgcolor(9);
                printf("0x%x", value);
                x--;
                address -= 10;
                sc_memoryGet(address, &value);
                mt_setbgcolor(4);
                mt_gotoXY(x, y);
                printf("0x%x", value);
                mt_gotoXY(23, 1);

                itoa(value, A);
                 print (value, A);

                break;
            case Down:

                if (address / 10 == 9) break;
                sc_memoryGet(address, &value);
                mt_gotoXY(x, y);
                mt_setbgcolor(9);
                printf("0x%x", value);
                x++;
                address += 10;
                sc_memoryGet(address, &value);
                mt_setbgcolor(4);
                mt_gotoXY(x, y);
                printf("0x%x", value);
                mt_gotoXY(23, 1);


                itoa(value, A);
                print (value, A);

                break;
            case Esc:
                break;
            case Save:

                f = fopen("Save.out", "wb");
                sc_memorySave(f);
                break;
            case Load:

                f = fopen("Save.out", "rb");
                sc_memoryLoad(f);
                break;
            case F5:

                scanf("%d", &value);
                sc_memorySet(address, value);
                mt_gotoXY(x, y);
                mt_setbgcolor(4);
                printf("0x%x", value);
                itoa(value, A);
                 print (value, A);
                mt_setbgcolor(9);
                mt_gotoXY(25, 1);
                printf("     ");

                break;
            case Run:
                Timer();
                break;
            case Reset:
                Signal();
                break;
        }
    }
	if (key == Reset) {

        Signal();
    }
	if (key == Esc) return 0;
	mt_setbgcolor (9);
	mt_gotoXY(23, 1);
	return 0;
}
