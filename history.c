#include "shell.h"

/**
 * history_get_file - A function to gets the history file
 * @dl_info: parameter struct
 *
 * Return: string containg allocated history file
 */

char *history_get_file(info_t *dl_info)
{
	char *buff, *dirt;

	dirt = _getenv(dl_info, "HOME=");
	if (!dirt)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirt) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strngcpy(buff, dirt);
	_strngcat(buff, "/");
	_strngcat(buff, HIST_FILE);
	return (buff);
}

/**
 * wrt_history - A function to creates a file, or appends to an existing file
 * @dl_info: the struct parameter
 *
 * Return: 1 on success, else -1
 */
int wrt_history(info_t *dl_info)
{
	ssize_t df;
	char *filename = history_get_file(dl_info);
	list_t *nodes = NULL;

	if (!filename)
		return (-1);

	df = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (df == -1)
		return (-1);
	for (nodes = dl_info->history; nodes; nodes = nodes->next)
	{
		_putsfd(nodes->str, df);
		_putfd('\n', df);
	}
	_putfd(BUF_FLUSH, df);
	close(df);
	return (1);
}

/**
 * rd_history - function to read history from a file
 * @dl_info: the parameter struct
 *
 * Return: return histcount if success, 0 otherwise
 */
int rd_history(info_t *dl_info)
{
	int x, last = 0, lncount = 0;
	ssize_t df, rdlent, fsize = 0;
	struct stat str;
	char *buff = NULL, *filename = history_get_file(dl_info);

	if (!filename)
		return (0);

	df = open(filename, O_RDONLY);
	free(filename);
	if (df == -1)
		return (0);
	if (!fstat(df, &str))
		fsize = str.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlent = read(df, buff, fsize);
	buff[fsize] = 0;
	if (rdlent <= 0)
		return (free(buff), 0);
	close(df);
	for (x = 0; x < fsize; x++)
		if (buff[x] == '\n')
		{
			buff[x] = 0;
			build_list_history(dl_info, buff + last, lncount++);
			last = x + 1;
		}
	if (last != x)
		build_list_history(dl_info, buff + last, lncount++);
	free(buff);
	dl_info->histcount = lncount;
	while (dl_info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(dl_info->history), 0);
	renumber_history(dl_info);
	return (dl_info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @dl_info: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @lncount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *dl_info, char *buff, int lncount)
{
	list_t *nodes = NULL;

	if (dl_info->history)
		nodes = dl_info->history;
	add_node_end(&nodes, buff, lncount);

	if (!dl_info->history)
		dl_info->history = nodes;
	return (0);
}

/**
 * renumber_history - A fuction to renumber history linked list after changes
 * @dl_info: A structure having potential arguments.
 *
 * Return: the new histcount
 */
int renumber_history(info_t *dl_info)
{
	list_t *nodes = dl_info->history;
	int x = 0;

	while (nodes)
	{
		nodes->num = x++;
		nodes = nodes->next;
	}
	return (dl_info->histcount = x);
}
