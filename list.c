#include "shell.h"

/**
 * new_node - adds a node at the beginning of the list
 * @hd: address of pointer to head node
 * @strng: strng field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *new_node(list_t **hd, const char *strng, int num)
{
	list_t *nw_head;

	if (!hd)
		return (NULL);
	nw_head = malloc(sizeof(list_t));
	if (!nw_head)
		return (NULL);
	_memset((void *)nw_head, 0, sizeof(list_t));
	nw_head->num = num;
	if (strng)
	{
		nw_head->strng = _strdup(strng);
		if (!nw_head->strng)
		{
			free(nw_head);
			return (NULL);
		}
	}
	nw_head->next = *hd;
	*hd = nw_head;
	return (nw_head);
}

/**
 * add_end_node - adds a node to the end of the list
 * @hd: address of pointer to head node
 * @strng: strng field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_end_node(list_t **hd, const char *strng, int num)
{
	list_t *nw_node, *nodes;

	if (!hd)
		return (NULL);

	nodes = *hd;
	nw_node = malloc(sizeof(list_t));
	if (!nw_node)
		return (NULL);
	_memset((void *)nw_node, 0, sizeof(list_t));
	nw_node->num = num;
	if (strng)
	{
		nw_node->strng = _strdup(strng);
		if (!nw_node->strng)
		{
			free(nw_node);
			return (NULL);
		}
	}
	if (nodes)
	{
		while (nodes->next)
			nodes = nodes->next;
		nodes->next = nw_node;
	}
	else
		*hd = nw_node;
	return (nw_node);
}

/**
 * strng_list_print - function that prints only the
 * strng element of a list_t linked list.
 * @y: A pointer to the first nodes
 *
 * Return: return the size of a list
 */
size_t strng_list_print(const list_t *y)
{
	size_t x = 0;

	while (y)
	{
		_puts(y->strng ? y->strng : "(nil)");
		_puts("\n");
		y = y->next;
		x++;
	}
	return (x);
}

/**
 * delete_nodes - deletes node at given index
 * @hd: address of pointer to first node
 * @edex: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_nodes(list_t **hd, unsigned int edex)
{
	list_t *nodes, *fmr_nodes;
	unsigned int x = 0;

	if (!hd || !*hd)
		return (0);

	if (!edex)
	{
		nodes = *hd;
		*hd = (*hd)->next;
		free(nodes->strng);
		free(nodes);
		return (1);
	}
	nodes = *hd;
	while (nodes)
	{
		if (x == edex)
		{
			fmr_nodes->next = nodes->next;
			free(nodes->strng);
			free(nodes);
			return (1);
		}
		x++;
		fmr_nodes = nodes;
		nodes = nodes->next;
	}
	return (0);
}

/**
 * free_lst - function that frees all nodes of a list
 * @hd_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_lst(list_t **hd_ptr)
{
	list_t *nodes, *next_node, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	nodes = hd;
	while (nodes)
	{
		next_node = nodes->next;
		free(nodes->strng);
		free(nodes);
		nodes = next_node;
	}
	*hd_ptr = NULL;
}
