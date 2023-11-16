#include "shell.h"

/**
 * discard_info - initializes info_t struct
 * @dl_info: struct address
 */
void discard_info(info_t *dl_info)
{
	dl_info->arg = NULL;
	dl_info->argv = NULL;
	dl_info->path = NULL;
	dl_info->argc = 0;
}

/**
 * ini_info - To initializes info_t struct
 * @dl_info: struct address
 * @avec: argument vector
 */
void ini_info(info_t *dl_info, char **avec)
{
	int x = 0;

	dl_info->fname = avec[0];
	if (dl_info->arg)
	{
		dl_info->argv = strngtow(dl_info->arg, " \t");
		if (!dl_info->argv)
		{

			dl_info->argv = malloc(sizeof(char *) * 2);
			if (dl_info->argv)
			{
				dl_info->argv[0] = _strngdup(dl_info->arg);
				dl_info->argv[1] = NULL;
			}
		}
		for (x = 0; dl_info->argv && dl_info->argv[x]; x++)
			;
		dl_info->argc = x;

		re_place_alias(dl_info);
		re_place_vars(dl_info);
	}
}

/**
 * free_dlinfo - frees info_t struct fields
 * @dl_info: struct address
 * @all: stands for true if releasing all fields
 */
void free_dlinfo(info_t *dl_info, int all)
{
	ffree(dl_info->argv);
	dl_info->argv = NULL;
	dl_info->path = NULL;
	if (all)
	{
		if (!dl_info->cmd_buf)
			free(dl_info->arg);
		if (dl_info->env)
			free_lst(&(dl_info->env));
		if (dl_info->history)
			free_lst(&(dl_info->history));
		if (dl_info->alias)
			free_lst(&(dl_info->alias));
		ffree(dl_info->enviromt);
			dl_info->enviromt = NULL;
		bfree((void **)dl_info->cmd_buf);
		if (dl_info->readfd > 2)
			close(dl_info->readfd);
		_sendchar(BUF_FLUSH);
	}
}
