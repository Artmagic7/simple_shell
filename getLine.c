#include "shell.h"

/**
 * input_buf - buffers chained instrctns
 * @info: Paramtr struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t v = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		v = getline(buf, &len_p, stdin);
#else
		v = _getline(info, buf, &len_p);
#endif
		if (v > 0)
		{
			if ((*buf)[v - 1] == '\n')
			{
				(*buf)[v - 1] = '\0'; /* remove trailing newline */
				v--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = v;
				info->cmd_buf = buf;
			}
		}
	}
	return (v);
}

/**
 * get_input - obtains a line without the newline
 * @info: Parametr struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t g, f, len;
	ssize_t v = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	v = input_buf(info, &buf, &len);
	if (v == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		f = g; /* init new iterator to current buf position */
		p = buf + g; /* get pointer for return */

		check_chain(info, buf, &f, g, len);
		while (f < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &f))
				break;
			f++;
		}

		g = f + 1; /* increment past nulled ';'' */
		if (g >= len) /* reached end of buffer? */
		{
			g = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (v); /* return length of buffer from _getline() */
}

/**
 * read_buf - study a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t v = 0;

	if (*i)
		return (0);
	v = read(info->readfd, buf, READ_BUF_SIZE);
	if (v >= 0)
		*i = v;
	return (v);
}

/**
 * _getline - win the next line of input from STDIN
 * @info: Parametr struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t g, len;
	size_t q;
	ssize_t v = 0, y = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		y = *length;
	if (g == len)
		g = len = 0;

	v = read_buf(info, buf, &len);
	if (v == -1 || (v == 0 && len == 0))
		return (-1);

	c = _strchr(buf + g, '\n');
	q = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, y, y ? y + q : q + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (y)
		_strncat(new_p, buf + g, q - g);
	else
		_strncpy(new_p, buf + g, q - g + 1);

	y += q - g;
	g = q;
	p = new_p;

	if (length)
		*length = y;
	*ptr = p;
	return (y);
}

/**
 * sigintHandler - jams ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
