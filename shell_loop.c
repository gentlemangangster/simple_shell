#include "shell.h"

/**
 * tmsh - main shell loop
 * @dl_info: the parameter & return info struct
 * @avct: the argument vector from main()
 *
 * Return: return value 0 on success, 1 on error, or error code
 */
int tmsh(info_t *dl_info, char **avct)
{
	ssize_t k = 0;
	int btin_ret = 0;

	while (k != -1 && btin_ret != -2)
	{
		discard_info(dl_info);
		if (interactive(dl_info))
			_putts("$ ");
		_eputstrgchar(BUF_FLUSH);
		k = get_inpts(dl_info);
		if (k != -1)
		{
			ini_info(dl_info, avct);
			btin_ret = btin_fnd(dl_info);
			if (btin_ret == -1)
				fnd_cmd(dl_info);
		}
		else if (interactive(dl_info))
			_sendchar('\n');
		free_dlinfo(dl_info, 0);
	}
	wrt_history(dl_info);
	free_dlinfo(dl_info, 1);
	if (!interactive(dl_info) && dl_info->status)
		exit(dl_info->status);
	if (btin_ret == -2)
	{
		if (dl_info->err_num == -1)
			exit(dl_info->status);
		exit(dl_info->err_num);
	}
	return (btin_ret);
}

/**
 * btin_fnd - function that finds a builtin command
 * @dl_info: the parameter & return info struct
 *
 * Return: -1 if the btin not found,
 *			0 if btin executed successfully,
 *			1 if btin found but not successful,
 *			-2 if btin signals exit()
 */
int btin_fnd(info_t *dl_info)
{
	int x, btin_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _shelexit},
		{"env", _tmenv},
		{"help", _tmhlp},
		{"history", _tmhistory},
		{"setenv", _tmsetenv},
		{"unsetenv", _tmunsetenv},
		{"cd", _tmcd},
		{"alias", _tmalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strgcmp(dl_info->argv[0], builtintbl[x].type) == 0)
		{
			dl_info->line_count++;
			btin_ret = builtintbl[x].func(dl_info);
			break;
		}
	return (btin_ret);
}

/**
 * fnd_cmd - A function finds a command in PATH
 * @dl_info: the parameter & return info struct
 *
 * Return: void
 */
void fnd_cmd(info_t *dl_info)
{
	char *path = NULL;
	int x, k;

	dl_info->path = dl_info->argv[0];
	if (dl_info->linecount_flag == 1)
	{
		dl_info->line_count++;
		dl_info->linecount_flag = 0;
	}
	for (x = 0, k = 0; dl_info->arg[x]; x++)
		if (!is_delimt(dl_info->arg[x], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_the_path(dl_info, _getenv(dl_info, "PATH="), dl_info->argv[0]);
	if (path)
	{
		dl_info->path = path;
		frk_cmd(dl_info);
	}
	else
	{
		if ((interactive(dl_info) || _getenv(dl_info, "PATH=")
			|| dl_info->argv[0][0] == '/') && dtm_if_cmd(dl_info, dl_info->argv[0]))
			frk_cmd(dl_info);
		else if (*(dl_info->arg) != '\n')
		{
			dl_info->status = 127;
			generate_error(dl_info, "not found\n");
		}
	}
}

/**
 * frk_cmd - functions that forks a an exec thread to run cmd
 * @dl_info: the parameter & return info struct
 *
 * Return: void
 */
void frk_cmd(info_t *dl_info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(dl_info->path, dl_info->argv, gt_enviromt(dl_info)) == -1)
		{
			free_dlinfo(dl_info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(dl_info->status));
		if (WIFEXITED(dl_info->status))
		{
			dl_info->status = WEXITSTATUS(dl_info->status);
			if (dl_info->status == 126)
				generate_error(dl_info, "Permission denied\n");
		}
	}
}
