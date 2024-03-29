#include "shell.h"

/**
 * _strlen - Returns the extent of a string
 * @s: String extent to check
 *
 * Return: Integer extent of string
 */
int _strlen(char *s)
{
	int g = 0;

	if (!s)
		return (0);

	while (*s++)
		g++;
	return (g);
}

/**
 * _strcmp - Executes lexicogarphic contrast of two strings.
 * @s1: the 1st string
 * @s2: the 2nd string
 *
 * Return: -ve if s1 < s2, +ve if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Confirms if needle begins with haystack
 * @haystack: string to explore
 * @needle: the substring to locate
 *
 * Return: Location of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Connects two strings
 * @dest: the location buffer
 * @src: The origin buffer
 *
 * Return: pointer to location buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
