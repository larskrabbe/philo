/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:45:46 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/27 05:36:13 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

pthread_mutex_t	*get_mutex_array(size_t len)
{
	pthread_mutex_t	*ptr;
	size_t			i;

	i = 0;
	ptr = malloc(sizeof(pthread_mutex_t) * len);
	if (ptr == NULL)
		return (0);//free error
	while (i < len)
	{
		if (pthread_mutex_init(&ptr[i], NULL))
			return (0);//free error
		i++;
	}
	return (ptr);
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

void	transform_args(t_input *input, int argc, char *argv[])
{
	get_next_arg(argc, argv);
	input->philosophers = simple_atoi(get_next_arg(argc, argv));
	input->time_to_die = simple_atoi(get_next_arg(argc, argv));
	input->time_to_eat = simple_atoi(get_next_arg(argc, argv));
	input->time_to_sleep = simple_atoi(get_next_arg(argc, argv));
	input->amount_to_eat = simple_atoi(get_next_arg(argc, argv));
	if (input->philosophers > 0)
	{
		input->forks = malloc(sizeof(int) * input->philosophers);
		memset(input->forks, 0, input->philosophers);
		gettimeofday(&input->start_time, NULL);
		input->fork_mutex = get_mutex_array(input->philosophers);
		pthread_mutex_init(&input->mutex, NULL);
	}
}
