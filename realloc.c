#include "shell.h"

/**
 **_memoryset - fills memory with a constant byte
 *@a: the pointer to the memory area
 *@d: the byte to fill *s with
 *@nmb: the amount of bytes to be filled
 *Return: value (a), a pointer to the memory area 
 */
char *_memoryset(char *a, char d, unsigned int nmb)
{
	unsigned int x;

	for (x = 0; x < n; x++)
		a[x] = d;
	return (a);
}

/**
 * ffree - frees a string of strings
 * @sst: string of strings
 */
void ffree(char **sst)
{
	char **a = sst;

	if (!sst)
		return;
	while (*sst)
		free(*sst++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *pttr, unsigned int old_sz, unsigned int new_sz)
{
	char *pt;

	if (!pttr)
		return (malloc(new_sz));
	if (!new_sz)
		return (free(pttr), NULL);
	if (new_sz == old_sz)
		return (pttr);

	pt = malloc(new_sz);
	if (!pt)
		return (NULL);

	old_sz = old_sz < new_sz ? old_sz : new_sz;
	while (old_size--)
		pt[old_sz] = ((char *)pttr)[old_sz];
	free(pttr);
	return (pt);
}
