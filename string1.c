#include "shell.h"

/**
 * _strcpy - Clones a string
 * @dest: The location
 * @src: the Origin
 *
 * Return: Pointer to location
 */
char *_strcpy(char *dest, char *src)
{
	int g = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[g])
	{
		dest[g] = src[g];
		g++;
	}
	dest[g] = 0;
	return (dest);
}

/**
 * _strdup - Copies a string
 * @str: The string to copy
 *
 * Return: Pointer to Copied string
 */
char *_strdup(const char *str)
{
	int distance = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		distance++;
	ret = malloc(sizeof(char) * (distance + 1));
	if (!ret)
		return (NULL);
	for (distance++; distance--;)
		ret[distance] = *--str;
	return (ret);
}

/**
 * _puts - Lists an input string
 * @str: String to be listed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int g = 0;

	if (!str)
		return;
	while (str[g] != '\0')
	{
		_putchar(str[g]);
		g++;
	}
}

/**
 * _putchar - List the charctr c to stdout
 * @c: Character to list
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int g;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || g >= WRITE_BUF_SIZE)
	{
		write(1, buf, g);
		g = 0;
	}
	if (c != BUF_FLUSH)
		buf[g++] = c;
	return (1);
}
