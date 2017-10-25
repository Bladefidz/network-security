#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

/**
 * Generate IP Address using rules
 * Compile
 * 	gcc -Wall genIp.c -o genIp
 * Run
 * 	Generate IP
 * 		./genIp <ip_with_x> <rules>
 * 	Help
 * 		./genIp -h
 */

/* Struct declarations */
struct Ranges
{
	int r;
	struct Ranges *next;
};

/* Global variables */
int INVALID_RULE = 0;
char *IP_HEAD;
char *IP_TAIL;

/* Prototype declarations */
void splitIP(char *y, int n);
void printIP(int x);
int printRangeIp(char *cmd, int n, int i);
int printRandomIp(char *cmd, int n, int i);
int printWhiteListIp(char *cmd, int n, int i);
void parseComplexCmd(char *cmd, int start, int end, int *tmp);

/* Main program */
int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		if (strcmp(argv[1], "-h") == 0)
		{
			printf("Print sequence of IP.\n");
			printf("Format : ./genIp <ip_with_x> <rules>\n");
			printf("Example:\n");
			printf("Generate sequence of 255 ip from .0 to .255: ./genIp 10.10.10.x\n");
			printf("Generate sequence of 10 ip from .0 to .9: ./genIp 10.10.10.x [10]\n");
			printf("Generate sequence of 10 ip in .55 to .65: ./genIp 10.10.10.x [10,=55-65]\n");
			printf("Generate random 10 ip: ./genIp 10.10.10.x [10,r]\n");
			printf("Generate list of 10 ip from .0 to .011, but not .1 and .2: ./genIp 10.10.10.x [10,!1!2]\n");
		}
		else
		{
			splitIP(argv[1], strlen(argv[1]));
			for (int i = 0; i < 256; ++i)
			{
				printIP(i);
			}
		}
	}
	else if (argc > 2)
	{
		if (argv[2][0] == '[')
		{
			int len = strlen(argv[2]);
			if (argv[2][len-1] == ']')
			{
				splitIP(argv[1], len);
				int ind = 1, n = 0;
				while (argv[2][ind] != ']' && argv[2][ind] != ',')
				{
					ind++;
				}
				for (int i = ind - 1; i > 0; i--)
				{
					n += (argv[2][i] - '0') * pow(10, (ind - (i+1)));
				}
				if (argv[2][ind] == '=')
				{
					ind = printRangeIp(argv[2], n, ind);
				}
				else if (argv[2][ind] == 'r')
				{
					ind = printRandomIp(argv[2], n, ind);
				}
				else if (argv[2][ind] == '!')
				{
					ind = printWhiteListIp(argv[2], n, ind);
				}
				else
				{
					for (int i = 0; i < n; i++)
					{
						printIP(i);
					}
				}
				if (argv[2][ind] != ']')
				{
					parseComplexCmd(argv[2], ind, len - 1, (int *) malloc(n));
				}
			}
			else
			{
				INVALID_RULE = 1;
			}
		}
		else
		{
			INVALID_RULE = 1;
		}

		if (INVALID_RULE)
		{
			printf("Invalid given rule.\n");
		}
	}
	else
	{
		printf("Try to get help using -h\n");
	}
	return 0;
}

/**
 * Split annotated IP to combine as full IP later.
 * @param y Annotated IP with 'x'
 * @param n Length of split IP
 */
void splitIP(char *y, int n)
{
	int i = 0, j = 0;
	for (; i < 15; i++)
	{
		if (y[i] == 'x')
		{
			break;
		}
		else if (y[i] == '.')
		{
			j++;
		}
	}
	if (i > 1)
	{
		IP_HEAD = (char *) malloc(i);
		for (int k = 0; k < i; ++k)
		{
			IP_HEAD[k] = y[k];
		}
	}
	else
	{
		IP_HEAD = NULL;
	}
	if (j < 3)
	{
		IP_TAIL = (char *) malloc((n - i - 1));
		j = 0;
		for (i = i + 1; i < n; i++)
		{
			IP_TAIL[j] = y[i];
		}
	}
	else
	{
		IP_TAIL = NULL;
	}
}

/**
 * Print full IP
 * @param x Generated number to replace 'x'
 */
void printIP(int x)
{
	if (IP_HEAD != NULL)
	{
		printf("%s", IP_HEAD);
	}
	printf("%d", x);
	if (IP_TAIL != NULL)
	{
		printf("%s", IP_TAIL);
	}
	printf("\n");
}

int printRangeIp(char *cmd, int n, int i)
{
	// while (cmd[2][i] != ']' && cmd[2][i] != ',')
	// {
	// 	i++;
	// }
	// for (int j = i - 1; j > 0; j--)
	// {
	// 	n += (cmd[2][i] - '0') * pow(10, (ind - (i+1)));
	// }
	return i;
}

int printRandomIp(char *cmd, int n, int i)
{
	return i;
}

int printWhiteListIp(char *cmd, int n, int i)
{
	return i;
}

/**
 * Parse command
 * @param cmd   Command
 * @param start Start index
 * @param end   End index
 */
void parseComplexCmd(char *cmd, int start, int end, int *tmp)
{
	if (start < end)
	{

	}
}