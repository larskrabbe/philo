/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_untils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:58:05 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/02 22:09:18 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

void	wait_until(struct timeval *time)
{
	while (get_time_stamp(time) < 0)
		usleep(10);
}

void	time_minus_mili(struct timeval *time, suseconds_t sub)
{
	time->tv_usec += sub;
	if (time->tv_usec > 1000000)
	{
		time->tv_sec += 1;
		time->tv_usec -= 1000000;
	}
}

void	time_plus_mili(struct timeval *time, suseconds_t sub)
{
	time->tv_usec += sub;
	if (time->tv_usec > 1000000)
	{
		time->tv_sec += 1;
		time->tv_usec -= 1000000;
	}
}

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
