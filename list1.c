#include "shell.h"

/**
 * lst_lent - function that determines length of linked list
 * @y: the pointer to first node
 *
 * Return: to return the size of list
 */
size_t lst_lent(const list_t *y)
{
	size_t x = 0;

	while (y)
	{
		y = y->next;
		x++;
	}
	return (x);
}

/**
 * lst_to_strngs - returns an array of strings of the list->strng
 * @hd: pointer to first node
 *
 * Return: return an array of strings
 */
char **lst_to_strngs(list_t *hd)
{
	list_t *nodes = hd;
	size_t x = lst_lent(hd), f;
	char **strngs;
	char *strng;

	if (!hd || !x)
		return (NULL);
	strngs = malloc(sizeof(char *) * (x + 1));
	if (!strngs)
		return (NULL);
	for (x = 0; nodes; nodes = nodes->next, x++)
	{
		strng = malloc(_strlent(nodes->strng) + 1);
		if (!strng)
		{
			for (f = 0; f < x; f++)
				free(strngs[f]);
			free(strngs);
			return (NULL);
		}

		strng = _strgcpy(strng, nodes->strng);
		strngs[x] = strng;
	}
	strngs[x] = NULL;
	return (strngs);
}


/**
 * print_lst - prints all elements of a list_t linked list
 * @y: pointer to first node
 *
 * Return: size of list
 */
size_t print_lst(const list_t *y)
{
	size_t x = 0;

	while (y)
	{
		_putts(change_number(y->num, 10, 0));
		_sendchar(':');
		_sendchar(' ');
		_putts(y->strng ? y->strng : "(nil)");
		_putts("\n");
		y = y->next;
		x++;
	}
	return (x);
}

/**
 * strt_node_with - returns node whose string starts with prefix
 * @nodes: pointer to list head
 * @prfix: string to match
 * @m: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *strt_node_with(list_t *nodes, char *prfix, char m)
{
	char *pt = NULL;

	while (nodes)
	{
		pt = begin_with(nodes->strng, prfix);
		if (pt && ((m == -1) || (*pt == m)))
			return (nodes);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * get_node_edex - A function that gets the index of a node
 * @hd: pointer to list head
 * @nodes: its a pointer to the node
 *
 * Return: to return index of node or -1
 */
ssize_t get_node_edex(list_t *hd, list_t *nodes)
{
	size_t x = 0;

	while (hd)
	{
		if (hd == nodes)
			return (x);
		hd = hd->next;
		x++;
	}
	return (-1);
}
