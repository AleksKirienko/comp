#include <stdio.h>
#include "lib.h"
#include "lib3.h"
#include "lib4.h"
#include "lib5.h"
#include "cu.h"

int address = 0;
int x = 2, y = 2;
int Instr = 0;
int valacc = 0;

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
		if (value < 32768)
		{
			bc_setbig(big, '+');
			bc_printbigchar (big,14, 2, 7, 2);
		}
		else 
		{
			bc_setbig(big, ' ');
			bc_printbigchar (big,14, 2, 7, 2);
 		}
		if (A[3] <= 'F' && A[3]>='0')
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
		else if (A[2] <= 'F' && A[2]>='0')
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
		else if (A[1] <= 'F' && A[1]>='0')
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
		else if (A[0] <= 'F' && A[0]>='0')
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
    if (tcgetattr(0, &term) == -1)
        return -1;
    if (regime == 1)
        term.c_lflag |= ICANON;
    else
    if (regime == 0)
        term.c_lflag &= ~ICANON;
    else
        return -1;

    if (sigint == 1)
        term.c_lflag |= ISIG;
    else
    if (sigint == 0)
        term.c_lflag &= ~ISIG;
    else
        return -1;
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
    else if (!strcmp(A, "q"))
        *key= Esc;
    else if (!strcmp(A, "i"))
        *key= Reset;
    else if (!strcmp(A, "r"))
        *key= Run;
    else if (!strcmp(A, "s"))
        *key= Save;
    else if (!strcmp(A, "l"))
        *key= Load;
    else if (!strcmp(A, "e"))
        *key= Enter;
    else if (!strcmp(A, "\E[17~"))
        *key= F6;
    else if (!strcmp(A, "\E[15~"))
        *key= F5;
    else if (!strcmp(A, "t"))
        *key= Step;

    rk_mytermregime(1, 1, 1, 1, 1);
    read_key(*key);
    return 0;
}

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
	for (i = 0;i<4;i++)
		s[i]=' ';
    if ((sign = n) < 0)  
        n = -n;          
    i = 0;
    do {  
	int x = n % 16;
	if (x>9)    
	{
		if (x==10) s[i++]  = 'A';
		if (x==11) s[i++]  = 'B';
		if (x==12) s[i++]  = 'C';
		if (x==13) s[i++]  = 'D';
		if (x==14) s[i++]  = 'E';
		if (x==15) s[i++]  = 'F';
	}
        else s[i++] = x + '0';   
    } while ((n /= 16) > 0);     
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
	mt_setbgcolor (4);
    mt_gotoXY(2, 2);
	printf("      ");
	mt_gotoXY(2, 2);

	if (value<32768)  printf("+");
	else printf(" ");
    printf("%x",value);
    mt_setbgcolor (9);
    mt_gotoXY(1, 28);

    printf("Memory");

    bc_box(1, 64, 3, 20);
    mt_gotoXY(1, 67);
	mt_setbgcolor(9);
    printf("Accumulator");

    bc_box(4, 64, 3, 20);
    mt_gotoXY(4, 65);
    printf("InstructionCounter");

    bc_box(7, 64, 3, 20);
    mt_gotoXY(7, 70);
    printf("Operation");

	int command,operand;
	sc_commandDecode(value, &command, &operand);
	mt_gotoXY(8, 71);
	printf("+%x : %x  ",command,operand);

    bc_box(10, 64, 3, 20);
    mt_gotoXY(10, 70);
    printf("Flags");
    mt_gotoXY(11, 68);
    printf("O E P M T");

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
    printf("q - escape ");
    //mt_gotoXY(19, 45);
   // printf("e - enter chars");
    mt_gotoXY(19, 45);
    printf("F5 - accumulator");
	mt_gotoXY(20, 45);
    printf("F6 - enter address");
	mt_gotoXY(21, 45);
    printf("T - Step");

    bc_box(13, 1, 10, 42);
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
	mt_gotoXY(23, 1);
}

void sighandler (int signo)
{
	alarm(0);
	sc_regInit();
	sc_memoryInit();
	printGUI();
}

void signalhandler(int signo)
{
    int value;
    char A[4];
    int big[2];
    if (CU(A) == -1) {
        alarm(0);
        return ;
    }
    if (address == 99)
    {
        alarm (0);

	Instr = address;
    mt_gotoXY(5, 65);
    mt_setbgcolor(9);
    printf ("+%x ", Instr);

	int command,operand;
	sc_commandDecode(value, &command, &operand);
	mt_gotoXY(8, 71);
	printf("+%x : %x  ",command,operand);
	return;
    }
	sc_memoryGet(address, &value);
    mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
	printf("      ");
	mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
    mt_setbgcolor(9);
    if (value<32768)  printf("+");
	else printf(" ");
    printf("%x", value);
    address++;
    sc_memoryGet(address, &value);
    mt_setbgcolor(4);
    mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
	printf("      ");
	mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
    if (value<32768)  printf("+");
	else printf(" ");
    printf("%x", value);

	Instr = address;
	mt_gotoXY(5, 65);
    mt_setbgcolor(9);
    printf ("+%x ", Instr);

	int command,operand;
	sc_commandDecode(value, &command, &operand);
	mt_gotoXY(8, 71);
	printf("+%x : %x  ",command,operand);
    itoa(value, A);
	print (value, A);
	//alarm(1);
	Timer();
}

void Signal(void)
{
    int value;
    valacc = 0;
    sc_regSet(T, 0);
   	mt_gotoXY(11, 76);
    mt_setbgcolor(9);
    printf("T");
   	mt_gotoXY(25, 1);

    sc_memoryGet(address, &value);
    mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
	printf("      ");
	mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
    mt_setbgcolor(9);
    if (value<32768)  printf("+");
	else printf(" ");
    printf("%x", value);
    //x = 2;
    //y = 2;
    address = 0;

    signal (SIGUSR1, sighandler);
    raise (SIGUSR1);

    mt_gotoXY(2, 67);
	mt_setbgcolor(9);
    if (valacc < 32768) printf ("+");
    else printf (" ");
    printf("%x   ", valacc);

    Instr = 0;
    mt_gotoXY(5, 65);
    mt_setbgcolor(9);
    printf ("+%x", Instr);

	int command,operand;
	sc_commandDecode(value, &command, &operand);
	mt_gotoXY(8, 71);
	printf("+%x : %x  ",command,operand);
	mt_setbgcolor(9);
}
void Timer (void)
{
    sc_regSet(T, 1);
   	mt_gotoXY(11, 76);
    mt_setbgcolor(4);
    printf("T");
   	mt_gotoXY(25, 1);
    struct itimerval nval, oval;
    signal (SIGALRM, signalhandler);

    nval.it_interval.tv_sec = 0;
	nval.it_interval.tv_usec = 200000;
	nval.it_value.tv_sec = 0;
	nval.it_value.tv_usec = 200000;

    setitimer (ITIMER_REAL, &nval, &oval);
}

int ReadAssemblerFile(int args, char *argv[])
{
	FILE* input = fopen (argv[1],"r");
	int address, command, operand, value;
	if (input == -1) return -1;
	while (!feof(input))
	{
		fread(&address, sizeof(int), 1, input);
		fread(&command, sizeof(int), 1, input);
		fread(&operand, sizeof(int), 1, input);
		if (command != 1)
			sc_commandEncode(command, operand, &value);
		else 
			value = operand;
		sc_memorySet(address, value);
	}
	fclose(input);
	return 0;
}

int read_key(enum keys key)
{
    FILE *f;
	int value;
	char A[4];
	int command, operand;
	sc_regGet (T, &value);
	if (value == 1 && key != Reset){
	    signal (SIGALRM, signalhandler);

        Instr = address;
        mt_gotoXY(5, 65);
        mt_setbgcolor(9);
        printf ("+%x ", Instr);

        mt_gotoXY(11, 76);
        mt_setbgcolor(4);
        printf("T");
        mt_gotoXY(25, 1);
	
        return 0;
	}
        switch (key) {
            case Right:

                if (address % 10 == 9) break;
                sc_memoryGet(address, &value);
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                mt_setbgcolor(9);
                if (value<32768)  printf("+");
				else printf(" ");
        		printf("%x", value);
                address++;
                sc_memoryGet(address, &value);
                mt_setbgcolor(4);
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                if (value<32768)  printf("+");
				else printf(" ");
        		printf("%x", value);
                mt_gotoXY(30, 1);

                itoa(value, A);
                print (value, A);

                Instr = address;
                mt_gotoXY(5, 65);
                mt_setbgcolor(9);
                printf ("+%x ", Instr);

				//int command,operand;
				sc_commandDecode(value, &command, &operand);
				mt_gotoXY(8, 71);
				printf("+%x : %x  ",command,operand);

                break;
            case Left:

                if (address % 10 == 0) break;
                sc_memoryGet(address, &value);
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                mt_setbgcolor(9);
                if (value<32768)  printf("+");
				else printf(" ");
        		printf("%x", value);
                address--;
                sc_memoryGet(address, &value);
                mt_setbgcolor(4);
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                if (value<32768)  printf("+");
				else printf(" ");
        		printf("%x", value);
                mt_gotoXY(30, 1);

                itoa(value, A);
                print (value, A);

                Instr = address;
                mt_gotoXY(5, 65);
                mt_setbgcolor(9);
                printf ("+%x ", Instr);

				//int command,operand;
				sc_commandDecode(value, &command, &operand);
				mt_gotoXY(8, 71);
				printf("+%x : %x  ",command,operand);
                break;
            case Up:

                if (address / 10 == 0) break;
                sc_memoryGet(address, &value);
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                mt_setbgcolor(9);
                if (value<32768)  printf("+");
				else printf(" ");
        	    printf("%x", value);
                address -= 10;
                sc_memoryGet(address, &value);
                mt_setbgcolor(4);
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                if (value<32768)  printf("+");
				else printf(" ");
        		printf("%x", value);
                mt_gotoXY(30, 1);

                itoa(value, A);
                print (value, A);

                Instr = address;
                mt_gotoXY(5, 65);
                mt_setbgcolor(9);
                printf ("+%x ", Instr);

				//int command,operand;
				sc_commandDecode(value, &command, &operand);
				mt_gotoXY(8, 71);
				printf("+%x : %x  ",command,operand);
                break;
            case Down:

                if (address / 10 == 9) break;
                sc_memoryGet(address, &value);
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                mt_setbgcolor(9);
                if (value<32768)  printf("+");
				else printf(" ");
        		printf("%x", value);
                address += 10;
                sc_memoryGet(address, &value);
                mt_setbgcolor(4);
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                if (value<32768)  printf("+");
				else printf(" ");
        		printf("%x", value);
                mt_gotoXY(30, 1);

                itoa(value, A);
                print (value, A);

                Instr = address;
                mt_gotoXY(5, 65);
                mt_setbgcolor(9);
                printf ("+%x ", Instr);

				//int command,operand;
				sc_commandDecode(value, &command, &operand);
				mt_gotoXY(8, 71);
				printf("+%x : %x  ",command,operand);
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
            case Enter:
                scanf("%d", &value);
                while (value>65535)
                {
                    mt_gotoXY(23, 1);
                    printf ("Error       ");
                    mt_gotoXY(24, 1);
                    printf("            ");
                    mt_gotoXY(24, 1);
                    scanf("%d", &value);
                }
                sc_memorySet(address, value);
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                mt_setbgcolor(4);
                if (value<32768)  printf("+");
                else printf(" ");
                printf("%x", value);
                itoa(value, A);
                print (value, A);
                mt_setbgcolor(9);
                mt_gotoXY(23, 10);
                printf("            ");
                mt_gotoXY(24, 1);
                printf("            ");
                mt_gotoXY(23, 10);

                //int command,operand;
                sc_commandDecode(value, &command, &operand);
                mt_gotoXY(8, 71);
                printf("+%x : %x  ",command,operand);
                break;
            case F6:
                sc_memoryGet(address, &value);
                int x1 = address;

                scanf("%d", &address);

                if (address>99)
                {
                    sc_regSet(M, 1);
                    mt_gotoXY(11, 74);
                    mt_setbgcolor(4);
                    printf("M");
                    address=x1;
                    mt_gotoXY(25, 1);
                    break;
                }
                mt_gotoXY(x1/10 + 2, (x1 % 10)*6+2 );
				printf("      ");
				mt_gotoXY(x1/10 + 2, (x1 % 10)*6+2 );
                mt_setbgcolor(9);
                if (value<32768)  printf("+");
				else printf(" ");
        		printf("%x", value);

				sc_memoryGet(address, &value);
                mt_setbgcolor(4);
				x=2+address/10;
				y = 2+address%10*6;
                mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
				printf("      ");
				mt_gotoXY(address/10 + 2, (address % 10)*6+2 );
                if (value<32768)  printf("+");
				else printf(" ");
        		printf("%x", value);
                mt_gotoXY(30, 1);

                itoa(value, A);
                print (value, A);

                Instr = address;
                mt_gotoXY(5, 65);
                mt_setbgcolor(9);
                mt_gotoXY(23, 10);
                printf("            ");
		        mt_gotoXY(24, 1);
                printf("            ");
		        mt_gotoXY(23, 10);
                printf ("+%x ", Instr);

				//int command,operand;
				sc_commandDecode(value, &command, &operand);
				mt_gotoXY(8, 71);
				printf("+%x : %x  ",command,operand);
                break;
            case Run:
                Timer();
                break;
            case Reset:
                Signal();
		break;
	    case Step:
		    signalhandler(SIGALRM);
		    alarm (0);
                break;
            case F5:
                scanf("%d", &valacc);
                while (valacc>65535)
                {
                    mt_gotoXY(23, 1);
                    printf ("Error       ");
                    mt_gotoXY(24, 1);
                    printf("            ");
                    mt_gotoXY(24, 1);
                    scanf("%d", &valacc);
                }
                mt_gotoXY(2, 67);
                if (valacc < 32768) printf ("+");
                else printf (" ");
                printf("%x   ", valacc);
                break;
            default:
                return -1;

        }
	if (key == Reset) {

        Signal();
    }
	if (key == Esc) return 0;
	mt_setbgcolor (9);
	mt_gotoXY(23, 1);
	printf("            ");
	mt_gotoXY(23, 1);
	return 0;
}
