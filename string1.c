#include "shell.h"

/**
 * _strgcpy - function that copies a string
 * @dst: the argument destination
 * @src: the argument source
 *
 * Return: pointer to destination
 */
char *_strgcpy(char *dst, char *src)
{
	int x = 0;

	if (dst == src || src == 0)
		return (dst);
	while (src[x])
	{
		dst[x] = src[x];
		x++;
	}
	dst[x] = 0;
	return (dst);
}

/**
 * _strngdup - funtion that duplicates a string
 * @strng: the argument string to duplicate
 *
 * Return: return a pointer to the duplicated string
 */
char *_strngdup(const char *strng)
{
	int lenth = 0;
	char *rt;

	if (strng == NULL)
		return (NULL);
	while (*strng++)
		lenth++;
	rt = malloc(sizeof(char) * (lenth + 1));
	if (!rt)
		return (NULL);
	for (lenth++; lenth--;)
		rt[lenth] = *--strng;
	return (rt);
}

/**
 *_putts - function prints an input string
 *@strng: the argument string to be printed
 *
 * Return: return no value
 */
void _putts(char *strng)
{
	int x = 0;

	if (!strng)
		return;
	while (strng[x] != '\0')
	{
		_sendchar(strng[x]);
		x++;
	}
}

/**
 * _sendchar - writes the character c to stdout
 * @d: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _sendchar(char d)
{
	static int x;
	static char buff[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buff, x);
		x = 0;
	}
	if (d != BUF_FLUSH)
		buff[x++] = d;
	return (1);
}
