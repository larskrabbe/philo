/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 01:49:52 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/12 04:11:03 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

long long	timeval_to_ll(struct timeval *start, struct timeval *end)
{
	long long	time;

	time = 0;
	time += (start->tv_sec - end->tv_sec * 1000000);
	if (start->tv_usec < end->tv_usec)
		time -= 1000000;
	time += (start->tv_usec - end->tv_usec);
	return (time);
}

void	milisleep(long long time)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	time_plus_mili(&timestamp, time * 1000);
	while (wait_until(&timestamp))
		usleep(100);
}

void	time_plus_mili(struct timeval *time, suseconds_t add)
{
	time->tv_usec += add;
	if (time->tv_usec > 1000000)
	{
		time->tv_sec += 1;
		time->tv_usec -= 1000000;
	}
}

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
