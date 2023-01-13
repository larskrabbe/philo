/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:45:46 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/12 04:05:17 by lkrabbe          ###   ########.fr       */
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

int	simple_atoi(char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (num != 0 && i != 0)
			num *= 10;
		num += str[i] - '0';
		i++;
		if (num > INT32_MAX)
			return (-1);
	}
	if (is_white_space(str[i]) == 1 || str[i] == '\0')
		return (num);
	return (-1);
}

int	transform_args(t_input *input, int argc, char *argv[])
{
	get_next_arg(argc, argv);
	input->philosophers = simple_atoi(get_next_arg(argc, argv));
	input->time_to_die = simple_atoi(get_next_arg(argc, argv));
	input->time_to_eat = simple_atoi(get_next_arg(argc, argv));
	input->time_to_sleep = simple_atoi(get_next_arg(argc, argv));
	input->amount_to_eat = simple_atoi(get_next_arg(argc, argv));
	if (check_input(input) == 0)
	{
		gettimeofday(&input->start_time, NULL);
		time_plus_mili(&input->start_time, 10000);
		input->fork_mutex = get_mutex_array(input->philosophers);
		input->mutex_arr = get_mutex_array(last_lock);
		input->death_check = malloc(sizeof(long) * input->philosophers + 1);
	}
	else
	{	
		printf("invalid input\n");
		return (1);
	}
	return (0);
}
