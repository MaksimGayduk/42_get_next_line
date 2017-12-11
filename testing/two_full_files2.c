/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgayduk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 14:05:58 by mgayduk           #+#    #+#             */
/*   Updated: 2017/12/11 15:34:27 by mgayduk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <fcntl.h>

#include <stdio.h>

int main(int argc __attribute__ ((unused)), char **argv __attribute__ ((unused)))
{
	char *line1 = NULL;
	char *line2 = NULL;
    int fd1;
    int fd2;
	int res1 = 1;
	int res2 = 1;

    fd1 = open(argv[1], O_RDONLY, 0);
    fd2 = open(argv[2], O_RDONLY, 0);

    while (res1 || res2)
    {
        res1 = get_next_line(fd1, &line1);
        printf("String readed fd: %i : %s\t: with result %i\n", fd1, line1, res1);
        res2 = get_next_line(fd2, &line2);
        printf("String readed fd: %i : %s\t: with result %i\n", fd2, line2, res2);
    }

    ft_strdel(&line1);
    ft_strdel(&line2);
	close(fd1);
	close(fd2);
	return (0);
}
