#include "shell.h"

/**
 * _tmenv - prints the current environment
 * @dl_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _tmenv(info_t *dl_info)
{
	print_list_str(dl_info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *dl_info, const char *gnm)
{
	list_t *nodes = dl_info->env;
	char *k;

	while (node)
	{
		k = starts_with(node->str, gnm);
		if (k && *k)
			return (k);
		nodes = nodes->next;
	}
	return (NULL);
}

/**
 * _tmsetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @dl_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _tmsetenv(dl_info_t *dl_info)
{
	if (dl_info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(dl_info, dl_info->argv[1], dl_info->argv[2]))
		return (0);
	return (1);
}

/**
 * _tmunsetenv - Remove an environment variable
 * @dl_info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _tmunsetenv(info_t *dl_info)
{
	int i;

	if (dl_info->argc == 1)
	{
		_eputs("Not upto expected arguements.\n");
		return (1);
	}
	for (i = 1; i <= dl_info->argc; i++)
		_unsetenv(dl_info, dl_info->argv[i]);

	return (0);
}

/**
 * addto_env_list - populates env linked list
 * @dl_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int addto_env_list(info_t *dl_info)
{
	list_t *nodes = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&nodes, environ[i], 0);
	dl_info->env = nodes;
	return (0);
}
