#include "shell.h"

/**
 * **strngtow - func to splits a string into words.
 * Repeat delimiters are ignored
 * @strng: the argumentbinput string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strngtow(char *strng, char *d)
{
	int x, j, k, m, numbwords = 0;
	char **n;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; strng[x] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(strng[x + 1], d) || !str[x + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!n)
		return (NULL);
	for (x = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(strng[x], d))
			x++;
		k = 0;
		while (!is_delim(strng[x + k], d) && strng[x + k])
			k++;
		n[j] = malloc((k + 1) * sizeof(char));
		if (!n[j])
		{
			for (k = 0; k < j; k++)
				free(n[k]);
			free(n);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			n[j][m] = strng[x++];
		n[j][m] = 0;
	}
	n[j] = NULL;
	return (n);
}

/**
 * **strngtow2 - func to splits a string into words
 * @str: the argument input string
 * @d: the argument delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strngtow2(char *strng, char d)
{
	int x, j, k, m, numbwords = 0;
	char **n;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	for (i = 0; strng[x] != '\0'; x++)
		if ((strng[x] != d && strng[x + 1] == d) ||
		    (strng[x] != d && !strng[x + 1]) || strng[x + 1] == d)
			numbwords++;
	if (numbwords == 0)
		return (NULL);
	n = malloc((1 + numbwords) * sizeof(char *));
	if (!n)
		return (NULL);
	for (x = 0, j = 0; j < numwords; j++)
	{
		while (strng[x] == d && strng[x] != d)
			x++;
		k = 0;
		while (strng[x + k] != d && strng[x + k] && strng[x + k] != d)
			k++;
		n[j] = malloc((k + 1) * sizeof(char));
		if (!n[j])
		{
			for (k = 0; k < j; k++)
				free(n[k]);
			free(n);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			n[j][m] = strng[x++];
		n[j][m] = 0;
	}
	n[j] = NULL;
	return (n);
}
