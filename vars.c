#include "shell.h"

/**
 * is_chain - Check if present char in buffer is a chain delimeter
 * @info: Paramtr struct
 * @buf: char buffer
 * @p: Location of present positn in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t f = *p;

	if (buf[f] == '|' && buf[f + 1] == '|')
	{
		buf[f] = 0;
		f++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[f] == '&' && buf[f + 1] == '&')
	{
		buf[f] = 0;
		f++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[f] == ';') /* located end of this command */
	{
		buf[f] = 0; /* sustitute semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = f;
	return (1);
}

/**
 * check_chain - Scans we should continue chaining based on last status
 * @info: Paramtr struct
 * @buf: Char buffer
 * @p: Location of present position in buf
 * @i: Begining position in buf
 * @len: The buf length
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t g, size_t len)
{
	size_t f = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[g] = 0;
			f = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[g] = 0;
			f = len;
		}
	}

	*p = f;
}

/**
 * replace_alias - Returns an aliases in the tokenized string
 * @info:Paramtr struct
 *
 * Return: 1 if returned, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int g;
	list_t *node;
	char *p;

	for (g = 0; g < 10; g++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Returns vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if returned, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int g = 0;
	list_t *node;

	for (g = 0; info->argv[g]; g++)
	{
		if (info->argv[g][0] != '$' || !info->argv[g][1])
			continue;

		if (!_strcmp(info->argv[g], "$?"))
		{
			replace_string(&(info->argv[g]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[g], "$$"))
		{
			replace_string(&(info->argv[g]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[g][1], '=');
		if (node)
		{
			replace_string(&(info->argv[g]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[g], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Returns string
 * @old: Location of old string
 * @new: New string
 *
 * Return: 1 if returned, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
