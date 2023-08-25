#include "shell.h"

/**
 * _erratoi - Transform a string to an integer
 * @s: the string to be tranformed
 * Return: 0 if no numbers in string, transformed number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int g = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (g = 0;  s[g] != '\0'; g++)
	{
		if (s[g] >= '0' && s[g] <= '9')
		{
			result *= 10;
			result += (s[g] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Lists an error message
 * @info: The parmtr & rtrn info struct
 * @estr: string housing specified error type
 * Return: 0 if no nmbrs in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function lists a decimal (integer) nmbr (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: Nmbr of char printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int g, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (g = 1000000000; g > 1; g /= 10)
	{
		if (_abs_ / g)
		{
			__putchar('0' + current / g);
			count++;
		}
		current %= g;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Tranformer function, a copy of itoa
 * @num: Nmbr
 * @base: base
 * @flags: Argumnt flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function restores first instance of '#' with '\0'
 * @buf: address of the string to alter
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int g;

	for (g = 0; buf[g] != '\0'; g++)
		if (buf[g] == '#' && (!g || buf[g - 1] == ' '))
		{
			buf[g] = '\0';
			break;
		}
}
