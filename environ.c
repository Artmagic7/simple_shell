#include "shell.h"

/**
 * _myenv - Lists the current environment
 * @info: Structure housing potential arguments. Used to keep
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Wins the value of an environ variable
 * @info: Structure housing potential arguments. Used to keep
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Adjust a new environment variable,
 *             or alter an existing one
 * @info: Structure housing potential arguments. Used to Keep
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Detach an environment variable
 * @info: Structure housing potential arguments. Used to keep
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int g;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (g = 1; g <= info->argc; g++)
		_unsetenv(info, info->argv[g]);

	return (0);
}

/**
 * populate_env_list - Occupies env linked list
 * @info: Structure housing potential arguments. Used to keep
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t g;

	for (g = 0; environ[g]; g++)
		add_node_end(&node, environ[g], 0);
	info->env = node;
	return (0);
}
