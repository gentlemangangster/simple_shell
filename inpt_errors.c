#include "shell.h"

/**
 *_eputstrg - prints an input string
 * @strng: the string to be printed
 *
 * Return: Nothing
 */
void _eputstrg(char *strng)
{
	int i = 0;

	if (!strng)
		return;
	while (strng[i] != '\0')
	{
		_eputstrgchar(strng[i]);
		i++;
	}
}

/**
 * _eputstrgchar - writes the character d to stderr
 * @d: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputstrgchar(char d)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buff, i);
		i = 0;
	}
	if (d != BUF_FLUSH)
		buff[i++] = d;
	return (1);
}

/**
 * _eputdf - writes the character d to given df
 * @d: The character to print
 * @df: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputdf(char d, int df)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(df, buff, i);
		i = 0;
	}
	if (d != BUF_FLUSH)
		buff[i++] = d;
	return (1);
}

/**
 *_putsdf - prints an input string
 * @strng: the string to be printed
 * @df: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsdf(char *strng, int df)
{
	int i = 0;

	if (!strng)
		return (0);
	while (*strng)
	{
		i += _eputdf(*strng++, df);
	}
	return (i);
}
