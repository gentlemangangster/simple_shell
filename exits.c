#include "shell.h"

/**
 **_strngcpy - A function that copies a string
 *@src: the source string to be copied to
 *@dst: this reperesent the destination string
 *@k: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strngcpy(char *dst, char *src, int k)
{
	int x, m;
	char *b = dst;

	x = 0;
	while (src[x] != '\0' && x < k - 1)
	{
		dst[x] = src[x];
		x++;
	}
	if (x < k)
	{
		m = x;
		while (m < k)
		{
			dst[m] = '\0';
			m++;
		}
	}
	return (b);
}

/**
 **_strngcat - Function use to concatenates two strings
 *@src: stand for the second string
 *@dst: reperesent the first string
 *@k: the maximum amount of bytes to be used
 *Return: the concatenated string
 */
char *_strngcat(char *dst, char *src, int k)
{
	int x, m;
	char *b = dst;

	x = 0;
	m = 0;
	while (dst[x] != '\0')
		x++;
	while (src[m] != '\0' && m < k)
	{
		dst[x] = src[m];
		x++;
		m++;
	}
	if (m < k)
		dst[x] = '\0';
	return (b);
}

/**
 **_strngchr - A function that searcheis a character in a string
 *@b: Reperesent the string to be parsed
 *@d: Reperesent the character to look for
 *Return: (b) a pointer to the memory area b
 */
char *_strngchr(char *b, char d)
{
	do {
		if (*b == d)
			return (b);
	} while (*b++ != '\0');

	return (NULL);
}
