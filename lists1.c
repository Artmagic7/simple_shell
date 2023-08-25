#include "shell.h"

/**
 * list_len - Dictates length of linked list
 * @h: pointer to 1st node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t g = 0;

	while (h)
	{
		h = h->next;
		g++;
	}
	return (g);
}

/**
 * list_to_strings - Gets back an array of strings of the list->str
 * @head: pointer to 1st node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t g = list_len(head), f;
	char **strs;
	char *str;

	if (!head || !g)
		return (NULL);
	strs = malloc(sizeof(char *) * (g + 1));
	if (!strs)
		return (NULL);
	for (g = 0; node; node = node->next, g++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (f = 0; f < g; f++)
				free(strs[f]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[g] = str;
	}
	strs[g] = NULL;
	return (strs);
}


/**
 * print_list - Copies all elements of a list_t linked list
 * @h: pointer to 1st node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t g = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		g++;
	}
	return (g);
}

/**
 * node_starts_with - Returns node whose string begins with prefix
 * @node: Pointer to list head
 * @prefix: string to match
 * @c: Next char after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gives the index of a node
 * @head: Pointer to the list head
 * @node: Pointer to node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t g = 0;

	while (head)
	{
		if (head == node)
			return (g);
		head = head->next;
		g++;
	}
	return (-1);
}
