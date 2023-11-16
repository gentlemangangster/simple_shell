#include "shell.h"

/**
 * _shelexit - Funtion to exits the shell
 * @dl_info: Structure holds important arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _shelexit(info_t *dl_info)
{
	int shexitcheck;

	if (dl_info->argv[1]) /* If there is an exit arguement */
	{
		shexitcheck = _erratoi(dl_info->argv[1]);
		if (shexitcheck == -1)
		{
			dl_info->status = 2;
			generate_error(dl_info, "Illegal number: ");
			_eputstrg(dl_info->argv[1]);
			_eputstrgchar('\n');
			return (1);
		}
		dl_info->err_num = _erratoi(dl_info->argv[1]);
		return (-2);
	}
	dl_info->err_num = -1;
	return (-2);
}

/**
 * _tmcd - changes the current directory of the process
 * @dl_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _tmcd(info_t *dl_info)
{
	char *d, *dirt, buf_fer[1024];
	int chdirt_rt;

	d = getcwd(buf_fer, 1024);
	if (!d)
		_putts("TODO: >>getcwd failure emsg here<<\n");
	if (!dl_info->argv[1])
	{
		dirt = _getenv(dl_info, "HOME=");
		if (!dirt)
			chdirt_rt = /* TODO: what should this be? */
				chdir((dirt = _getenv(dl_info, "PWD=")) ? dirt : "/");
		else
			chdirt_rt = chdir(dirt);
	}
	else if (_strgcmp(dl_info->argv[1], "-") == 0)
	{
		if (!_getenv(dl_info, "OLDPWD="))
		{
			_putts(d);
			_sendchar('\n');
			return (1);
		}
		_putts(_getenv(dl_info, "OLDPWD=")), _sendchar('\n');
		chdirt_rt = /* TODO: what should this be? */
			chdir((dirt = _getenv(dl_info, "OLDPWD=")) ? dirt : "/");
	}
	else
		chdirt_rt = chdir(dl_info->argv[1]);
	if (chdirt_rt == -1)
	{
		generate_error(dl_info, "can't cd to ");
		_eputstrg(dl_info->argv[1]), _eputstrgchar('\n');
	}
	else
	{
		_setenv(dl_info, "OLDPWD", _getenv(dl_info, "PWD="));
		_setenv(dl_info, "PWD", getcwd(buf_fer, 1024));
	}
	return (0);
}

/**
 * _tmhlp - changes the current directory of the process
 * @dl_info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _tmhlp(info_t *dl_info)
{
	char **array_arg;

	array_arg = dl_info->argv;
	_putts("help call works. Function not yet added \n");
	if (0)
		_putts(*array_arg);
	return (0);
}
