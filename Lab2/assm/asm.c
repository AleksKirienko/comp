#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int checkcommand (char *str)
{
	if (!strcmp("READ",str)) return 0x10;
	else if (!strcmp("WRITE",str)) return 0x11;
    else if (!strcmp("LOAD",str)) return 0x20;
    else if (!strcmp("STORE",str)) return 0x21;
    else if (!strcmp("JUMP",str)) return 0x40;
    else if (!strcmp("JNEG",str)) return 0x41;       
	else if (!strcmp("JZ",str)) return 0x42;
 	else if (!strcmp("HALT",str)) return 0x43;
	else if (!strcmp("ADD",str)) return 0x30;
    else if (!strcmp("SUB",str)) return 0x31;       
	else if (!strcmp("DIVIDE",str)) return 0x32;
 	else if (!strcmp("MUL",str)) return 0x33;
    else if (!strcmp("JNP",str)) return 0x59;
    else if (!strcmp("SUBC",str)) return 0x66;
	else if (!strcmp("=",str)) return 1;
	else return -1;
}
int main(int args, char* argv[])
{
	FILE* input = fopen (argv[1],"r");
	FILE* output = fopen (argv[2],"wb");
	char s[200];
	char str[7];
	int address, command, operand = 0, i;
	if (input == NULL) 
		return -1;
	while (fgets(s, 200, input))
	{
		address = (s[0]-'0') * 10 +(s[1]-'0');
		i = 3;
		while (s[i] != ' ')
		{
			str[i - 3] = s[i];
			++i;
		}
		str[i - 3] = '\0'; 
		//printf("%s\n",s);
		command = checkcommand (str);
		if (command == -1) 
		{ 
			printf ("Incorrect command\n"); 
			return -1;
		}
		for (; s[i] == ' '; ++i)
			;
		for (; s[i] != ' ' && s[i] != '\0'; ++i)
			if (s[i] != '+')
				operand = operand * 10 + s[i] - '0';
		fwrite(&address, sizeof(int), 1, output);
		fwrite(&command, sizeof(int), 1, output);
		fwrite(&operand, sizeof(int), 1, output);
		operand = 0;
	}
	fclose(input);
	fclose(output);
	return 0;
}
