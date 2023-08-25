#include "shell.h"

/**
 * is_cmd - dictates if a file is an executable command
 * @info: the info struct
 * @path: The path to file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - copies characters
 * @pathstr: the PATH string
 * @start: Begining index
 * @stop: Ending index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int g = 0, q = 0;

	for (q = 0, g = start; g < stop; g++)
		if (pathstr[g] != ':')
			buf[q++] = pathstr[g];
	buf[q] = 0;
	return (buf);
}

/**
 * find_path - Locates this cmd in the PATH string
 * @info: Info struct
 * @pathstr:PATH string
 * @cmd: cmd to find
 *
 * Return: full path of cmd if located or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int g = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[g] || pathstr[g] == ':')
		{
			path = dup_chars(pathstr, curr_pos, g);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[g])
				break;
			curr_pos = g;
		}
		g++;
	}
	return (NULL);
}
