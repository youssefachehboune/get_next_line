/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachehbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:48:23 by yachehbo          #+#    #+#             */
/*   Updated: 2021/11/21 17:29:28 by yachehbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_bonus(int fd, char *buffer)
{
	char	buff[BUFFER_SIZE + 1];
	int		bytes_read;

	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		buff[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, buff);
	}
	return (buffer);
}

char	*get_line_bonus(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (0);
	i = -1;
	while (buffer[++i] && buffer[i] != '\n')
		line[i] = buffer[i];
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*new_buff_bonus(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;
	int		len;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free (buffer);
		return (0);
	}
	len = ft_strlen(buffer) - i;
	new_buffer = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_buffer)
		return (0);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free (buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffers[200000];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffers[fd] = ft_read_bonus(fd, buffers[fd]);
	if (!buffers[fd])
		return (0);
	line = get_line_bonus(buffers[fd]);
	buffers[fd] = new_buff_bonus(buffers[fd]);
	return (line);
}
