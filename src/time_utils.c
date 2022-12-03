/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:58:05 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 12:40:03 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"


/**
 * @brief waits until a specific time is reached
 * 
 * @param time pointer to the time when the
 */
void	wait_until(struct timeval *time)
{
	while (get_time_stamp(time) < 0)
		usleep(10);
}

/**
 * @brief returns the current timestamp 
 * 
 * @param timestamp starttime
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
 * @brief reduce the total time inside of the timeval by the amount in nanosec
 * 
 * @param time the time that will be change
 * @param sub the amount that will reduce the time
 */
void	time_minus_mili(struct timeval *time, suseconds_t sub)
{
	time->tv_usec -= sub;
	while (time->tv_usec < 0)
	{
		time->tv_sec -= 1;
		time->tv_usec += 1000000;
	}
}

/**
 * @brief reduce the total time inside of the timeval by the amount in nanosec
 * 
 * @param time the time that will be change
 * @param plus the amount that will reduce the time
 */
void	time_plus_mili(struct timeval *time, suseconds_t plus)
{
	time->tv_usec += plus;
	while (time->tv_usec > 1000000)
	{
		time->tv_sec += 1;
		time->tv_usec -= 1000000;
	}
}

//TODO check it
/**
 * @brief More accurat version of the usleep funktion
 * 
 * @param time the time in miliseconed that will be waited
 */
void	milisleep(unsigned int time)
{
	// long long			dif_time;
	// struct timeval		start_time;
	// struct timeval		current_time;

	// gettimeofday(&current_time, NULL);
	// gettimeofday(&start_time, NULL);
	// dif_time = timeval_to_ll(&start_time, &current_time);
	// while (time - dif_time > 100)
	// {
	// 	usleep(dif_time * 0.8);
	// 	dif_time = timeval_to_ll(&start_time, &current_time);
	// }
	usleep(time * 1000);
}
