#include "shell.h"

/**
 * bfree - A func that frees a pointer and NULLs the address
 * @pttr: this stand for the address of pointer to be free
 *
 * Return: value 1 is return if freed, otherwise 0.
 */
int bfree(void **pttr)
{
	if (pttr && *pttr)
	{
		free(*pttr);
		*pttr = NULL;
		return (1);
	}
	return (0);
}
