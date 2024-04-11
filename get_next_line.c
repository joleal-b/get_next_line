/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark <jpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:14:34 by joleal-b          #+#    #+#             */
/*   Updated: 2023/11/30 09:23:32 by joleal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)str;
	while (p[i])
	{
		if (p[i] == (unsigned char)c)
			return (&p[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return (&p[i]);
	return (0);
}

static char	*first_line(char *file)
{
	size_t	size;
	char	*line;

	size = 0;
	if (!file[size])
		return (NULL);
	while (file[size] != '\n' && file[size])
		size++;
	line = ft_calloc((size + 2), sizeof(char));
	if (file[size] == '\n' || file[size] == '\0')
		ft_strlcpy(line, file, size + 1);
	if (file[size] == '\n')
		line[size++] = '\n';
	return (line);
}

static char	*new_file(char *file)
{
	size_t	size;
	size_t	file_size;
	char	*rest;

	size = 0;
	while (file[size] != '\n' && file[size])
		size++;
	if (!file[size])
	{
		free(file);
		return (NULL);
	}
	size++;
	file_size = ft_strlen(file) - size;
	rest = ft_substr(file, size, file_size);
	free(file);
	return (rest);
}

static char	*start_file(int fd, char *file)
{
	char	*temp;
	char	*buff;
	int		read_bytes;

	if (ft_strchr(file, '\n'))
		return (file);
	read_bytes = 1;
	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	while (!ft_strchr(file, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(file);
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		temp = file;
		file = ft_strjoin(temp, buff);
		free(temp);
	}
	free(buff);
	return (file);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*file;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!file)
		file = ft_calloc(1, 1);
	file = start_file(fd, file);
	if (!file)
		return (NULL);
	next_line = first_line(file);
	file = new_file(file);
	return (next_line);
}

/*#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/
