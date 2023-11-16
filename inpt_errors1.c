#include "shell.h"

/**
 * _eratoi - changes a string to an integer
 * @k: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _eratoi(char *k)
{
	int i = 0;
	unsigned long int otpt = 0;

	if (*k == '+')
		k++;  /* TODO: why does this make main return 255? */
	for (i = 0;  k[i] != '\0'; i++)
	{
		if (k[i] >= '0' && k[i] <= '9')
		{
			otpt *= 10;
			otpt += (k[i] - '0');
			if (otpt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (otpt);
}

/**
 * generate_error - A function that prints an error message
 * @dl_info: the parameter & return info struct
 * @estrng: the string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void generate_error(info_t *dl_info, char *estrng)
{
	_eputstrg(dl_info->fname);
	_eputstrg(": ");
	generate_d(dl_info->line_count, STDERR_FILENO);
	_eputstrg(": ");
	_eputstrg(dl_info->argv[0]);
	_eputstrg(": ");
	_eputstrg(estrng);
}

/**
 * generate_d - A function that prints a decimal (integer) number (base 10)
 * @inpt: the input
 * @df: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int generate_d(int inpt, int df)
{
	int (*__putchar)(char) = _sendchar;
	int i, cnt = 0;
	unsigned int _abs_, curnt;

	if (df == STDERR_FILENO)
		__putchar = _eputstrgchar;
	if (inpt < 0)
	{
		_abs_ = -inpt;
		__putchar('-');
		cnt++;
	}
	else
		_abs_ = inpt;
	curnt = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + curnt / i);
			cnt++;
		}
		curnt %= i;
	}
	__putchar('0' + curnt);
	cnt++;

	return (cnt);
}

/**
 * change_number - change the function, a clone of itoa
 * @numb: number
 * @base: base
 * @nflags: argument flags
 *
 * Return: string
 */
char *change_number(long int numb, int base, int nflags)
{
	static char buff[50];
	static char *ary;
	char *pttr;
	char sgn = 0;
	unsigned long j = numb;

	if (!(nflags & CONVERT_UNSIGNED) && numb < 0)
	{
		j = -numb;
		sgn = '-';

	}
	ary = nflags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pttr = &buff[49];
	*pttr = '\0';

	do	{
		*--pttr = ary[j % base];
		j /= base;
	} while (j != 0);

	if (sgn)
		*--pttr = sgn;
	return (pttr);
}

/**
 * remv_comments - A function that replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void remv_comments(char *buff)
{
	int a;

	for (a = 0; buff[a] != '\0'; a++)
		if (buff[a] == '#' && (!a || buff[a - 1] == ' '))
		{
			buff[a] = '\0';
			break;
		}
}
