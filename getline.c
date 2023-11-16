#include "shell.h"

/**
 * input_buff - function buffers chained commands
 * @dl_info: the parameter struct
 * @buff: this is the address of buffer
 * @lent: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buff(info_t *dl_info, char **buff, size_t *lent)
{
	ssize_t t = 0;
	size_t lent_pt = 0;

	if (!*lent) /* if no difference in the buffer, fill it */
	{
		/*bfree((void **)dl_info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, signintHandler);
#if USE_GETLINE
		t = getline(buff, &lent_pt, stdin);
#else
		t = _get_line(dl_info, buff, &lent_pt);
#endif
		if (t > 0)
		{
			if ((*buff)[t - 1] == '\n')
			{
				(*buff)[t - 1] = '\0'; /* delete trailing newline */
				t--;
			}
			dl_info->linecount_flag = 1;
			remv_comments(*buff);
			build_list_history(dl_info, *buff, dl_info->histcount++);
			/* if (_strngchr(*buff, ';')) is command chain? */
			{
				*lent = t;
				dl_info->cmd_buf = buff;
			}
		}
	}
	return (t);
}

/**
 * get_inpts - function to obtain a line minus the newline
 * @dl_info: it is the struct parameter
 *
 * Return: bytes read
 */
ssize_t get_inpts(info_t *dl_info)
{
	static char *buff; /* the ';' chain command buffer */
	static size_t x, m, lent;
	ssize_t t = 0;
	char **buff_p = &(dl_info->arg), *pttr;

	_sendchar(BUF_FLUSH);
	t = input_buff(dl_info, &buff, &lent);
	if (t == -1) /* EOF */
		return (-1);
	if (lent)	/* there is commands left in the buffer chain  */
	{
		m = x; /* init new iterator to current buff position */
		pttr = buff + x; /* get pointer for return */

		chck_chain(dl_info, buff, &m, x, lent);
		while (m < lent) /* iterate to semicolon or end */
		{
			if (te_chain(dl_info, buff, &m))
				break;
			m++;
		}

		x = m + 1; /* increment past nulled ';'' */
		if (x >= lent) /* reached end of buffer? */
		{
			x = lent = 0; /* to readjust position and length */
			dl_info->cmd_buf_type = CMD_NORM;
		}

		*buff_p = pttr; /* pass back pointer to current command position */
		return (_strlent(pttr)); /* return length of current command */
	}

	*buff_p = buff; /* else prevent a chain, pass back buffer from _getline() */
	return (t); /* return length of buffer from _getline() */
}

/**
 * read_buff - A function that reads a buffer
 * @dl_info: parameter struct
 * @buff: buffer
 * @x: size
 *
 * Return: t
 */
ssize_t read_buff(info_t *dl_info, char *buff, size_t *x)
{
	ssize_t t = 0;

	if (*x)
		return (0);
	t = read(dl_info->readdf, buff, READ_BUF_SIZE);
	if (t >= 0)
		*x = t;
	return (t);
}

/**
 * _get_line - gets the next line of input from STDIN
 * @dl_info: parameter struct
 * @pttr: address of pointer to buffer, preallocated or NULL
 * @lenth: size of preallocated ptr buffer if not NULL
 *
 * Return: m
 */
int _get_line(info_t *dl_info, char **pttr, size_t *lenth)
{
	static char buff[READ_BUF_SIZE];
	static size_t x, lent;
	size_t z;
	ssize_t t = 0, m = 0;
	char *pt = NULL, *new_pt = NULL, *g;

	pt = *pttr;
	if (pt && lenth)
		m = *lenth;
	if (x == lent)
		x = lent = 0;

	t = read_buff(dl_info, buff, &lent);
	if (t == -1 || (t == 0 && lent == 0))
		return (-1);

	g = _strngchr(buff + x, '\n');
	z = g ? 1 + (unsigned int)(g - buff) : lent;
	new_pt = _realloc(pt, m, m ? m + z : z + 1);
	if (!new_pt) /* MALLOC FAILURE! */
		return (pt ? free(pt), -1 : -1);

	if (s)
		_strngcat(new_pt, buff + x, z - x);
	else
		_strngcpy(new_pt, buff + x, z - x + 1);

	m += z - x;
	x = z;
	pt = new_pt;

	if (lenth)
		*lenth = m;
	*pttr = pt;
	return (m);
}

/**
 * signintHandler - the function that blocks ctrl-C
 * @sign_num: the signal number
 *
 * Return: void
 */
void signintHandler(__attribute__((unused))int sign_num)
{
	_putts("\n");
	_putts("$ ");
	_sendchar(BUF_FLUSH);
}
