/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 02:15:37 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/27 03:53:47 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

int	is_white_space(int a)
{
	if (a == ' ' || a == '\n' || a == '\t')
		return (1);
	return (0);
}

char	*get_next_arg(int argc, char *argv[])
{
	static char	*ptr = NULL;
	static int	argcount = 0;
	int			i;

	if (argv == NULL || argv[argcount] == NULL || argcount > argc)
		return (NULL);
	i = 0;
	if (argcount == 0 && ptr == NULL)
		ptr = argv[argcount];
	else
		while (is_white_space(ptr[i]) == 0 && ptr[i] != '\0')
			i++;
	while (is_white_space(ptr[i]) && ptr[i] != '\0')
		i++;
	while (ptr == NULL || ptr[i] == '\0')
	{
		argcount++;
		ptr = argv[argcount];
		i = 0;
		while (ptr != NULL && is_white_space(ptr[i]) && ptr[i] != '\0')
			i++;
		if (ptr == NULL || ptr[i] == '\0')
			return (ptr += i);
	}
	return (ptr += i);
}
