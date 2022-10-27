/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statechange.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:29:03 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/27 05:40:07 by lkrabbe          ###   ########.fr       */
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
	return (time);
}

/**
 * @brief prints the current timestamp 
 * and the philophor that change the state with the new state
 * 
 * @param philosopher the philosopher who change state
 * @param str the new state
 */
void	statemessage(int philosopher, char *str, \
struct timeval *start_time, t_philosophor *brain)
{
	pthread_mutex_lock(&brain->input->mutex);
	printf("%li %i %s\n", get_time_stamp(start_time), philosopher, str);
	pthread_mutex_unlock(&brain->input->mutex);
}