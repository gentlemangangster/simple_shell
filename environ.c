#include "shell.h"

/**
 * _tmenv - prints the current environment
 * @dl_info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _tmenv(info_t *dl_info)
{
	strng_list_print(dl_info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @dl_info: Structure containing potential arguments. Used to maintain
 * @gnm: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *dl_info, const char *gnm)
{
	list_t *nodes = dl_info->env;
	char *k;

	while (nodes)
	{
		k = begin_with(nodes->strng, gnm);
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
int _tmsetenv(info_t *dl_info)
{
	if (dl_info->argc != 3)
	{
		_eputstrg("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenvmt(dl_info, dl_info->argv[1], dl_info->argv[2]))
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
	int x;

	if (dl_info->argc == 1)
	{
		_eputstrg("Not upto expected arguements.\n");
		return (1);
	}
	for (x = 1; x <= dl_info->argc; x++)
		_unsetenv(dl_info, dl_info->argv[x]);

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
	size_t x;

	for (x = 0; environ[x]; x++)
		add_end_node(&nodes, environ[x], 0);
	dl_info->env = nodes;
	return (0);
}
