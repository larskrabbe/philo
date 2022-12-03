/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statecycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 01:51:06 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 14:45:22 by lkrabbe          ###   ########.fr       */
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

void	*philocycle(void *param)
{
	t_phil	*philo;

	philo = param;
	while (philo->death_occured)
	{
		send_request(philo);
		pthread_mutex_lock(philo->philo_mutex);
		statemessage("take left fork", philo);
		statemessage("take right fork", philo);
		statemessage("eats", philo);
		milisleep(philo->input.time_to_eat);
		statemessage("sleeping", philo);
		milisleep(philo->input.time_to_sleep);
	}
	return (philo);
}

void	pthread_main(t_phil *philo_array, t_waiter *waiter)
{
	int			i;
	pthread_t	*pthread_array;
	pthread_t	waiter_pthread;

	pthread_array = malloc(sizeof(pthread_t) * waiter->max);
	if (pthread_array == NULL)
		return ;
	i = start_philo(philo_array, pthread_array, waiter->max);
	if (i == waiter->max)
	{
		if (pthread_create(&waiter_pthread, NULL, \
		philocycle, &philo_array[i]) != 0)
			*waiter->deat_occurred = TRUE;
		else
			pthread_join(waiter_pthread, NULL);
	}
	join_philo(pthread_array, i);
}
