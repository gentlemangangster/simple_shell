#include "shell.h"

/**
 * te_chain - test if current char in buffer is a chain delimeter
 * @dl_info: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int te_chain(info_t *dl_info, char *buff, size_t *p)
{
	size_t m = *p;

	if (buff[m] == '|' && buff[m + 1] == '|')
	{
		buff[m] = 0;
		m++;
		dl_info->cmd_buf_type = CMD_OR;
	}
	else if (buff[m] == '&' && buff[m + 1] == '&')
	{
		buff[m] = 0;
		m++;
		dl_info->cmd_buf_type = CMD_AND;
	}
	else if (buff[m] == ';') /* found end of this command */
	{
		buff[m] = 0; /* replace the semicolon with null */
		dl_info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = m;
	return (1);
}

/**
 * chck_chain - checks we should continue chaining based on last status
 * @dl_info: the parameter struct
 * @buff: the char buffer
 * @p: address of current position in buf
 * @x: starting position in buf
 * @lent: length of buf
 *
 * Return: Void
 */
void chck_chain(info_t *dl_info, char *buff, size_t *p, size_t x, size_t lent)
{
	size_t m = *p;

	if (dl_info->cmd_buf_type == CMD_AND)
	{
		if (dl_info->status)
		{
			buff[x] = 0;
			m = lent;
		}
	}
	if (dl_info->cmd_buf_type == CMD_OR)
	{
		if (!dl_info->status)
		{
			buff[x] = 0;
			m = lent;
		}
	}

	*p = m;
}

/**
 * re_place_alias - replaces an aliases in the tokenized string
 * @dl_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int re_place_alias(info_t *dl_info)
{
	int x;
	list_t *nodes;
	char *p;

	for (x = 0; x < 10; x++)
	{
		nodes = node_starts_with(dl_info->alias, dl_info->argv[0], '=');
		if (!nodes)
			return (0);
		free(dl_info->argv[0]);
		p = _strngchr(nodes->strng, '=');
		if (!p)
			return (0);
		p = _strngdup(p + 1);
		if (!p)
			return (0);
		dl_info->argv[0] = p;
	}
	return (1);
}

/**
 * re_place_vars - replaces vars in the tokenized string
 * @dl_info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int re_place_vars(info_t *dl_info)
{
	int x = 0;
	list_t *nodes;

	for (x = 0; dl_info->argv[x]; x++)
	{
		if (dl_info->argv[x][0] != '$' || !dl_info->argv[x][1])
			continue;

		if (!_strngcmp(dl_info->argv[x], "$?"))
		{
			re_place_string(&(dl_info->argv[x]),
				_strngdup(change_number(dl_info->status, 10, 0)));
			continue;
		}
		if (!_strngcmp(dl_info->argv[x], "$$"))
		{
			re_place_string(&(dl_info->argv[x]),
				_strngdup(change_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(dl_info->env, &dl_info->argv[x][1], '=');
		if (node)
		{
			re_place_string(&(dl_info->argv[x]),
				_strngdup(_strngchr(node->strng, '=') + 1));
			continue;
		}
		re_place_string(&dl_info->argv[x], _strngdup(""));

	}
	return (0);
}

/**
 * re_place_string - replaces string
 * @old: address of old argument string
 * @nw: new argument string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int re_place_string(char **old, char *nw)
{
	free(*old);
	*old = nw;
	return (1);
}
