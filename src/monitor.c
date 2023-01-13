/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 04:19:50 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/13 14:42:10 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

void	check_for_dead_man_walking(t_input *input, int *death_flag)
{
	long int	time;
	int			i;

	if (*input->deat_occurred == TRUE)
		*death_flag = TRUE;
	i = 0;
	time = get_time_stamp(&input->start_time);
	while (i < input->philosophers && *death_flag == FALSE)
	{
		if (input->death_check[i] < time)
		{
			printf("%li %i died\n", \
			time, i + 1);
			*input->deat_occurred = TRUE;
			*death_flag = TRUE;
		}
		i++;
	}
}

void	monitor(t_input *input)
{
	int		death_flag;

	death_flag = FALSE;
	while (death_flag == FALSE)
	{
		pthread_mutex_lock(&input->mutex_arr[end]);
		if ((*input->end) + 1 >= input->philosophers)
		{
			pthread_mutex_unlock(&input->mutex_arr[end]);
			break ;
		}
		pthread_mutex_unlock(&input->mutex_arr[end]);
		pthread_mutex_lock(&input->mutex_arr[death_check]);
		check_for_dead_man_walking(input, &death_flag);
		pthread_mutex_unlock(&input->mutex_arr[death_check]);
		usleep(500);
	}
}
