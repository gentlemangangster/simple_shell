#include "shell.h"

/**
 * _strlent - function returns the length of a string
 * @m: the argument string length to check
 *
 * Return: return integer length of string
 */
int _strlent(char *m)
{
	int x = 0;

	if (!m)
		return (0);

	while (*m++)
		x++;
	return (x);
}

/**
 * _strgcmp - performs lexicogarphic comparison of two strangs.
 * @m1: the argument first strang
 * @m2: the argument second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strgcmp(char *m1, char *m2)
{
	while (*m1 && *m2)
	{
		if (*m1 != *m2)
			return (*m1 - *m2);
		m1++;
		m2++;
	}
	if (*m1 == *m2)
		return (0);
	else
		return (*m1 < *m2 ? -1 : 1);
}

/**
 * begin_with - function that checks if needle starts with haystack
 * @haystck: argument string to search
 * @nidle: argument substring to find
 *
 * Return: to return address of next char of haystack or NULL
 */
char *begin_with(const char *haystck, const char *nidle)
{
	while (*nidle)
		if (*nidle++ != *haystck++)
			return (NULL);
	return ((char *)haystck);
}

/**
 * _strgcat - funtion concatenates two strings
 * @dst: the argument destination buffer
 * @src: the argument source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strgcat(char *dst, char *src)
{
	char *rt = dst;

	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = *src;
	return (rt);
}
