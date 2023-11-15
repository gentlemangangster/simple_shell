#include "shell.h"

/**
 * main - the function entry point that start the program
 * @acnt: stand for arg count
 * @avct: stand for arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int acnt, char **avct)
{
	info_t dl_info[] = { INFO_INIT };
	int df = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (df)
		: "r" (df));

	if (acnt == 2)
	{
		df = open(avct[1], O_RDONLY);
		if (df == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputstrg(avct[0]);
				_eputstrg(": 0: Can't open ");
				_eputstrg(avct[1]);
				_eputstrgchar('\n');
				_eputstrgchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		dl_info->readfd = df;
	}
	addto_env_list(dl_info);
	rd_history(dl_info);
	tmsh(dl_info, avct);
	return (EXIT_SUCCESS);
}
