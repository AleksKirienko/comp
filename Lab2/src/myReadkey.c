#include <stdio.h>
#include <termios.h>
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
int rk_mytermrestore
{
	struct termios term;
	FILE *f = fopen ("load.in", "rb");
	if (!f) return -1;
	fread (&term, sizeof(term),1, f);
	if (tcsetattr(0, &term) == -1) return -1;
	fclose (f);
	return 0;
}
