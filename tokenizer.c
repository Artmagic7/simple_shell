#include "shell.h"

/**
 * **strtow - Divides a string into words. Replicated delimiters
 * are ignored
 * @str: Input string
 * @d: Delimeter string
 * Return: Pointer to an order of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int g, f, q, e, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (g = 0; str[g] != '\0'; g++)
		if (!is_delim(str[g], d) && (is_delim(str[g + 1], d) || !str[g + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (g = 0, f = 0; f < numwords; f++)
	{
		while (is_delim(str[g], d))
			g++;
		q = 0;
		while (!is_delim(str[g + q], d) && str[g + q])
			q++;
		s[f] = malloc((q + 1) * sizeof(char));
		if (!s[f])
		{
			for (q = 0; q < f; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (e = 0; e < q; e++)
			s[f][e] = str[g++];
		s[f][e] = 0;
	}
	s[f] = NULL;
	return (s);
}

/**
 * **strtow2 - Divides a string into words
 * @str: Input string
 * @d: Delimeter
 * Return: Pointer to an group of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int g, f, q, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (g = 0; str[g] != '\0'; g++)
		if ((str[g] != d && str[g + 1] == d) ||
				    (str[g] != d && !str[g + 1]) || str[g + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (g = 0, f = 0; f < numwords; f++)
	{
		while (str[g] == d && str[g] != d)
			g++;
		q = 0;
		while (str[g + q] != d && str[g + q] && str[g + q] != d)
			q++;
		s[f] = malloc((q + 1) * sizeof(char));
		if (!s[f])
		{
			for (q = 0; q < f; q++)
				free(s[q]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < q; m++)
			s[f][m] = str[g++];
		s[f][m] = 0;
	}
	s[f] = NULL;
	return (s);
}
