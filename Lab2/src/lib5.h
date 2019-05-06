#ifndef LIB5_H
#define LIB5_H
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <signal.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>


enum keys{Right, Left, Up, Down, Esc, Reset, Run, Save, Load, F5, F6};
void timer (void);
int rk_readkey (enum keys *);
int rk_mytermsave ();
int rk_mytermrestore ();
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int read_key (enum keys key);
void sighandler (int signo);
void signalhandler(int signo);
void Timer (void);
void Signal(void);
void printGUI (void);

#endif
