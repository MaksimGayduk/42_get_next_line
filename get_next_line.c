/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 14:03:55 by mgayduk           #+#    #+#             */
/*   Updated: 2017/12/07 17:13:55 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void fill_and_cut(char **line, char **buffer, char *line_end)
{
	size_t len;
	char *temp;

	len = line_end - *buffer;
	if (*line)
		ft_strdel(line);
	*line = ft_strnew(len);
	if (*line)
		ft_memcpy(*line, *buffer, len);
	temp = *buffer;
	*buffer = ft_strdup(++line_end);
	ft_strdel(&temp);
}

static int read_source(const int fd, char **buffer)
{
	int		bytes;
	char	*temp;
	char	*temp2;

	temp = ft_strnew(BUFF_SIZE);
	temp2 = *buffer;
	if ((bytes = read(fd, temp, BUFF_SIZE)) == -1)
		return (ERROR);
	*buffer = ft_strjoin(*buffer, temp);
	ft_strdel(&temp);
	ft_strdel(&temp2);
	return (bytes);
}

static int	fetch_line(const int fd, char **buffer, char **line, int bytes)
{
	char	*line_end;

	if (!(line_end = ft_strchr(*buffer, '\n')) && bytes)
	{
		bytes = read_source(fd, buffer);
		return (fetch_line(fd, buffer, line, bytes));
	}
	if ((bytes > 0 && line_end) || (!bytes && ft_strlen(*buffer)))
	{
		fill_and_cut(line, buffer, line_end);
		return (1);
	}
	if (bytes == -1)
		return (ERROR);
	fill_and_cut(line, buffer, *buffer);
	ft_strdel(buffer);
	return (FILE_END);
}

t_list *get_file(const int fd, t_list *head)
{
	t_list *temp;

	while (head)
	{
		if (head->content_size == fd)
			return (head);
		temp = head;
		head = head->next;
	}
	ft_lstadd_back(&temp, ft_lstnew(ft_strnew(BUFF_SIZE), fd));
	temp = temp->next;
	return (temp);

}

int	get_next_line(const int fd, char **line)
{
	static t_list *head;
	char	*buffer;
	t_list *file;

	if (fd < 0)
		return (ERROR);
	if (!head)
	{
		head = ft_lstnew(ft_strnew(BUFF_SIZE), fd);
		file = head;
	}
	else
	{
		file = get_file(fd, head);
		buffer = file->content;
	}
	if (!buffer)
		return (ERROR);
	return(fetch_line(fd, (char **)&(file->content), line, 1));
}
