/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statecycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 01:51:06 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/11/30 15:51:14 by lkrabbe          ###   ########.fr       */
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
	usleep(time * 1000);
}

/**
 * @brief send the waiter process a request to get unlock
 * 
 */
void	send_request(t_phil *philo)
{
	pthread_mutex_lock(philo->request_mutex);
		*philo->request = 1;
	pthread_mutex_unlock(philo->request_mutex);
}

void	philocycle(t_phil *philo)
{
	while (philo->death_occured)
	{
		send_request(philo);
		pthread_mutex_lock(philo->philo_mutex);
		statemessage("take left fork", philo);
		statemessage("take right fork", philo);
		statemessage("eats", philo);
		milisleep(philo->input->time_to_eat);
		statemessage("sleeping", philo);
		milisleep(philo->input->time_to_sleep);
	}
}
