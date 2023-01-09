/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statechange.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:29:03 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/09 20:42:09 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

/**
 * @brief returns the current timestamp 
 * 
 * @param timestamp the struct where the seconds and nanoseconds are stored
 */
long	get_time_stamp(struct timeval *start_time)
{
	struct timeval	timestamp;
	long			time;

	gettimeofday(&timestamp, NULL);
	timestamp.tv_sec -= start_time->tv_sec;
	timestamp.tv_usec -= start_time->tv_usec;
	if (timestamp.tv_usec < 0)
	{
		timestamp.tv_sec--;
		timestamp.tv_usec += 1000000;
	}
	time = timestamp.tv_sec * 1000;
	time += timestamp.tv_usec / 1000;
	// printf("time = %li", time);
	return (time);
}

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
	if (brain->death_flag == TRUE)
		return ;
	time = get_time_stamp(&brain->start_time);
	printf("%li %i %s\n",time, brain->name, str);
	pthread_mutex_unlock(&brain->input->mutex_arr[death_check]);
}
