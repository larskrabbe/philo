/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:45:46 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/25 20:20:19 by lkrabbe          ###   ########.fr       */
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

void	transform_args(t_input *input)
{
	input->philosophers = 200;
	input->time_to_die = 300;
	input->time_to_eat = 100;
	input->time_to_sleep = 100;
	input->amount_to_eat = 20;
	input->forks = malloc(sizeof(int) * input->philosophers);
	memset(input->forks, 0, input->philosophers);
	gettimeofday(&input->start_time, NULL);
	input->fork_mutex = get_mutex_array(input->philosophers);
	pthread_mutex_init(&input->mutex, NULL);
}
