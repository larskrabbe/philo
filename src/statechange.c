/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statechange.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:29:03 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/12 09:57:10 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

/**
 * @brief prints the current timestamp 
 * and the philophor that change the state with the new state
 * 
 * @param philosopher the philosopher who change state
 * @param str the new state
 */
void	statemessage(char *str, t_phil *brain)
{
	long int	time;

	pthread_mutex_lock(&brain->input->mutex_arr[death_check]);
	if (*brain->input->deat_occurred == TRUE)
		brain->death_flag = TRUE;
	else if (brain->death_flag == FALSE)
	{
		time = get_time_stamp(&brain->start_time);
		if (time >= *brain->death_check)
		{
			printf("%lims %i died\n", time, brain->name);
			*brain->input->deat_occurred = TRUE;
		}
		else
			printf("%lims %i %s\n", time, brain->name, str);
	}
	pthread_mutex_unlock(&brain->input->mutex_arr[death_check]);
}

void	eatmessage(char *str, t_phil *brain)
{
	long int	time;

	pthread_mutex_lock(&brain->input->mutex_arr[death_check]);
	if (*brain->input->deat_occurred == TRUE)
	{
		brain->death_flag = TRUE;
		pthread_mutex_unlock(&brain->input->mutex_arr[death_check]);
		return ;
	}
	time = get_time_stamp(&brain->start_time);
	if (time >= *brain->death_check)
	{
		printf("%lims %i died\n", time, brain->name);
		*brain->input->deat_occurred = TRUE;
	}
	else
		printf("%lims %i %s\n%lims %i is eating\n", \
		time, brain->name, str, time, brain->name);
	*brain->death_check = time + brain->input->time_to_die;
	brain->eat_count++;
	if (brain->input->amount_to_eat != -1 && \
		brain->eat_count >= brain->input->amount_to_eat && \
		*brain->input->deat_occurred != TRUE)
		brain->death_flag = TRUE;
	pthread_mutex_unlock(&brain->input->mutex_arr[death_check]);
}
