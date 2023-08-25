#include "shell.h"

/**
 **_strncpy - Clones a string
 *@dest: The terminus string to be copied to
 *@src: The origin string
 *@n: The qty of characters to be clone
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int g, f;
	char *s = dest;

	g = 0;
	while (src[g] != '\0' && g < n - 1)
	{
		dest[g] = src[g];
		g++;
	}
	if (g < n)
	{
		f = g;
		while (f < n)
		{
			dest[f] = '\0';
			f++;
		}
	}
	return (s);
}

/**
 **_strncat - Connects two strings
 *@dest: the 1st string
 *@src: the 2nd string
 *@n: the QTY of bytes to be maximally used
 *Return: the connected string
 */
char *_strncat(char *dest, char *src, int n)
{
	int g, f;
	char *s = dest;

	g = 0;
	f = 0;
	while (dest[g] != '\0')
		g++;
	while (src[f] != '\0' && f < n)
	{
		dest[g] = src[f];
		g++;
		f++;
	}
	if (f < n)
		dest[g] = '\0';
	return (s);
}

/**
 **_strchr - Finds character in a string
 *@s: the string to be parsed
 *@c: the character to locate
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
