#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @dt_info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *dt_info)
{
	return (isatty(STDIN_FILENO) && dt_info->readfd <= 2);
}

/**
 * is_delimt - checks if character is a delimeter
 * @d: the char to check
 * @de_limt: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimt(char d, char *de_limt)
{
	while (*de_limt)
		if (*de_limt++ == d)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @d: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @e: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *e)
{
	int k, sign_t = 1, flags = 0, outpt;
	unsigned int otptrest = 0;

	for (k = 0; e[k] != '\0' && flag != 2; k++)
	{
		if (e[i] == '-')
			sign_t *= -1;

		if (e[k] >= '0' && e[k] <= '9')
		{
			flags = 1;
			otptrest *= 10;
			otptrest += (e[k] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (sign_t == -1)
		outpt = -otoprest;
	else
		outpt = otoprest;

	return (outpt);
}
