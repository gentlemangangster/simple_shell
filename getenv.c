#include "shell.h"

/**
 * gt_enviromt - returns the string array copy of our environ
 * @dl_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **gt_enviromt(info_t *dl_info)
{
	if (!dl_info->environ || dl_info->env_changed)
	{
		dl_info->environ = list_to_strings(dl_info->env);
		dl_info->env_changed = 0;
	}

	return (dl_info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @dl_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @varb: the string env var property
 */
int _unsetenv(info_t *dl_info, char *varb)
{
	list_t *nodes = dl_info->env;
	size_t x = 0;
	char *pttr;

	if (!nodes || !varb)
		return (0);

	while (nodes)
	{
		pttr = begin_with(nodes->strng, varb);
		if (pttr && *pttr == '=')
		{
			dl_info->env_changed = delete_node(&(dl_info->env), x);
			x = 0;
			nodes = dl_info->env;
			continue;
		}
		nodes = nodes->next;
		X++;
	}
	return (dl_info->env_changed);
}

/**
 * _setenvmt - Initialize a new environment variable,
 *             or modify an existing one
 * @dl_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @varb: the string env var property
 * @value: the string env varb value
 *  Return: Always 0
 */
int _setenvmt(info_t *dl_info, char *varb, char *value)
{
	char *buff = NULL;
	list_t *nodes;
	char *pttr;

	if (!varb || !value)
		return (0);

	buff = malloc(_strlent(varb) + _strlent(value) + 2);
	if (!buff)
		return (1);
	_strngcpy(buff, varb);
	_strngcat(buff, "=");
	_strngcat(buff, value);
	nodes = dl_info->env;
	while (nodes)
	{
		pttr = begin_with(nodes->strng, varb);
		if (pttr && *pttr == '=')
		{
			free(nodes->strng);
			nodes->strng = buff;
			dl_info->env_changed = 1;
			return (0);
		}
		nodes = nodes->next;
	}
	add_end_node(&(dl_info->env), buff, 0);
	free(buff);
	dl_info->env_changed = 1;
	return (0);
}
