#ifndef LIB5_H
#define LIB5_H

#include <stdio.h>
#include <termios.h>
enum {Right, Left, Up, Down, Esc, Reset, Run, Save, Load, F5, F6};

int read_key (enum keys *);
int rk_mytermsave ();
int rk_mytermrestore ();
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);

#endif