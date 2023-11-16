#include "shell.h"

/**
 * dtm_if_cmd - determines if a file is an executable command
 * @dl_info: stand for the info struct
 * @paths: is the path to the file
 *
 * Return: value 1 is returned if true, 0 otherwise
 */
int dtm_if_cmd(info_t *dl_info, char *paths)
{
	struct stat strct;

	(void)dl_info;
	if (!paths || stat(paths, &strct))
		return (0);

	if (strct.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dups_char - to duplicates functions characters
 * @pathstrng: It is the path of the string
 * @strt: starting index
 * @stop: stopping index
 *
 * Return: return a pointer to new buffer
 */
char *dups_char(char *pathstrng, int strt, int stop)
{
	static char buff[1024];
	int x = 0, j = 0;

	for (j = 0, x = strt; x < stop; x++)
		if (pathstrng[x] != ':')
			buff[j++] = pathstrng[x];
	buff[j] = 0;
	return (buff);
}

/**
 * find_the_path - function that finds cmd in the PATH string
 * @dl_info: the info struct
 * @pathstrng: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd to return if found or NULL
 */
char *find_the_path(info_t *dl_info, char *pathstrng, char *cmd)
{
	int x = 0, curr_post = 0;
	char *paths;

	if (!pathstrng)
		return (NULL);
	if ((_strlent(cmd) > 2) && begin_with(cmd, "./"))
	{
		if (dtm_if_cmd(dl_info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstrng[x] || pathstrng[x] == ':')
		{
			paths = dups_char(pathstrng, curr_post, x);
			if (!*paths)
				_strgcat(paths, cmd);
			else
			{
				_strgcat(paths, "/");
				_strgcat(paths, cmd);
			}
			if (dtm_if_cmd(dl_info, paths))
				return (paths);
			if (!pathstrng[x])
				break;
			curr_post = x;
		}
		x++;
	}
	return (NULL);
}
