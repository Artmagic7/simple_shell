#include "shell.h"

/**
 * _eputs - Lists an input string
 * @str: the string to be listed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int g = 0;

	if (!str)
		return;
	while (str[g] != '\0')
	{
		_eputchar(str[g]);
		g++;
	}
}

/**
 * _eputchar - Commits the character c to stderr
 * @c: The character to list
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int g;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || g >= WRITE_BUF_SIZE)
	{
		write(2, buf, g);
		g = 0;
	}
	if (c != BUF_FLUSH)
		buf[g++] = c;
	return (1);
}

/**
 * _putfd - Commits the character c to given fd
 * @c: The character to list
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int g;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || g >= WRITE_BUF_SIZE)
	{
		write(fd, buf, g);
		g = 0;
	}
	if (c != BUF_FLUSH)
		buf[g++] = c;
	return (1);
}

/**
 * _putsfd - Lists an input string
 * @str: the string to be listed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int g = 0;

	if (!str)
		return (0);
	while (*str)
	{
		g += _putfd(*str++, fd);
	}
	return (g);
}
