#include "shell.h"

/**
 * _memset - Loads memory with a constant byte
 * @s: Pointer to the memory area
 * @b: Byte to fill *s with
 * @n: Qty of bytes to be filled
 * Return: (s) pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int g;

	for (g = 0; g < n; g++)
		s[g] = b;
	return (s);
}

/**
 * ffree - Releases a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - Reassigns a block of memory
 * @ptr: pointer to former malloc'ated block
 * @old_size: byte size of former block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
