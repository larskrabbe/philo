/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statecycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 01:51:06 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/11/29 19:19:00 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

long long	timeval_to_ll(struct timeval *start, struct timeval *end)
{
	long long	time;

	time = 0;
	time += (start->tv_sec - end->tv_sec * 1000000);
	if (start->tv_usec - end->tv_usec < 0)
	{
		time -= 1000000;
	}
	time += (start->tv_usec - end->tv_usec);
	return (time);
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
		usleep(time * 0.8);
}

void	philocycle(t_phil *philo)
{
	statemessage("take left fork", philo);
	statemessage("take right fork", philo);
	statemessage("eats", philo);
	milisleep(philo->input->time_to_eat);
	statemessage("sleeping", philo);
	milisleep(philo->input->time_to_sleep);
}
