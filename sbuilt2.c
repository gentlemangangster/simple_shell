#include "shell.h"

/**
 * _tmhistory - displays the history list, one command by line, preceded
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
 * conv_alias - sets alias to string
 * @dl_info: parameter struct
 * @strng: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int conv_alias(info_t *dl_info, char *strng)
{
	char *k, d;
	int rt;

	k = _strgchr(strng, '=');
	if (!k)
		return (1);
	d = *k;
	*k = 0;
	rt = delete_node(&(dl_info->alias),
		get_node_edex(dl_info->alias, node_starts_with(dl_info->alias, strng, -1)));
	*k = d;
	return (rt);
}

/**
 * sett_alias - sets alias to string
 * @dl_info: parameter struct
 * @strng: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int sett_alias(info_t *dl_info, char *strng)
{
	char *k;

	k = _strgchr(strng, '=');
	if (!k)
		return (1);
	if (!*++k)
		return (unsett_alias(dl_info, strng));

	unsett_alias(dl_info, strng);
	return (new_node(&(dl_info->alias), strng, 0) == NULL);
}

/**
 * generate_alias - prints an alias string
 * @nodes: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int generate_alias(list_t *nodes)
{
	char *k = NULL, *y = NULL;

	if (nodes)
	{
		k = _strgchr(nodes->strng, '=');
		for (y = nodes->strng; y <= k; y++)
			_sendchar(*y);
		_sendchar('\'');
		_putts(k + 1);
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
	char *k = NULL;
	list_t *nodes = NULL;

	if (dl_info->argc == 1)
	{
		nodes = dl_info->alias;
		while (nodes)
		{
			generate_alias(nodes);
			nodes = nodes->next;
		}
		return (0);
	}
	for (x = 1; dl_info->argv[x]; x++)
	{
		k = _strgchr(dl_info->argv[x], '=');
		if (k)
			sett_alias(dl_info, dl_info->argv[x]);
		else
			generate_alias(node_starts_with(dl_info->alias, dl_info->argv[x], '='));
	}

	return (0);
}
