#include "shell.h"

/**
 * _tmhistory - Is a func displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @dl_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _tmhistory(info_t *dl_info)
{
	print_list(dl_info->history);
	return (0);
}

/**
 * unsett_alias - sets alias to string
 * @dl_info: parameter struct
 * @strng: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsett_alias(info_t *dl_info, char *strng)
{
	char *p, c;
	int ret;

	p = _strngchr(strng, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_nodes(&(dl_info->alias),
		get_node_edex(dl_info->alias, node_starts_with(dl_info->alias, strng, -1)));
	*p = c;
	return (ret);
}

/**
 * sett_alias - sets alias to string
 * @dl_info: parameter struct
 * @strng: the string alias
 *
 * Return: return always 0 on success, 1 on error
 */
int sett_alias(info_t *dl_info, char *strng)
{
	char *p;

	p = _strgchr(strng, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unsett_alias(dl_info, strng));

	unsett_alias(dl_info, strng);
	return (add_end_node(&(dl_info->alias), strng, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @nodes: the alias nodes
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *nodes)
{
	char *p = NULL, *a = NULL;

	if (nodes)
	{
		p = _strgchr(nodes->strng, '=');
		for (a = nodes->strng; a <= p; a++)
			_sendchar(*a);
		_sendchar('\'');
		_putts(p + 1);
		_putts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _tmalias - mimics the alias builtin (man alias)
 * @dl_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _tmalias(info_t *dl_info)
{
	int x = 0;
	char *p = NULL;
	list_t *nodes = NULL;

	if (dl_info->argc == 1)
	{
		nodes = dl_info->alias;
		while (nodes)
		{
			print_alias(nodes);
			nodes = nodes->next;
		}
		return (0);
	}
	for (x = 1; dl_info->argv[x]; x++)
	{
		p = _strngchr(dl_info->argv[x], '=');
		if (p)
			sett_alias(dl_info, dl_info->argv[x]);
		else
			print_alias(node_starts_with(dl_info->alias, dl_info->argv[x], '='));
	}

	return (0);
}
