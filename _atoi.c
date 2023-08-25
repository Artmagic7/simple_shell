#include "shell.h"

/**
 * interactive - gives true when shell is interactive mode
 * @info: Struct location
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Confirms charctr is a delimeter
 * @c: the char to cnfrm
 * @delim: Delimetr string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Cnfrms for alphabetic charctr
 * @b: Charctr to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - Translates a string to an integer
 * @s: the string to translate
 * Return: 0 if no nmbrs in string, trnslted nmbr otherwise
 */

int _atoi(char *s)
{
	int g, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (g = 0; s[g] != '\0' && flag != 2; g++)
	{
		if (s[g] == '-')
			sign *= -1;

		if (s[g] >= '0' && s[g] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[g] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
