/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 14:05:58 by mgayduk           #+#    #+#             */
/*   Updated: 2017/12/07 17:10:10 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>

#include <stdio.h>

int main(int argc __attribute__ ((unused)), char **argv __attribute__ ((unused)))
{
	char *line;
    int fd;
	int res;

    fd = open(argv[1], O_RDONLY, 0);

    while (get_next_line(fd, &line) > 0)
    {
    	printf("String readed fd: %i : %s\t: with result %i\n", fd, line, res);
    	ft_strdel(&line);
    }

	close(fd);
	return (0);
}
