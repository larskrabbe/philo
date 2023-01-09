/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statecycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 01:51:06 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/09 13:54:39 by lkrabbe          ###   ########.fr       */
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
	send_request(philo);
	while (!philo->death_occured)
	{
		// send_request(philo);
		//printf("lock %i\n", philo->name);
		pthread_mutex_lock(philo->philo_mutex);
		statemessage("eats", philo);
		milisleep(philo->input.time_to_eat);
		send_request(philo);
		statemessage("sleeping", philo);
		milisleep(philo->input.time_to_sleep);
	}
	return (philo);
}

void	pthread_main(t_phil *philo_array, t_waiter *waiter)
{
	int			i;
	pthread_t	*pthread_array;

	printf("philo main start\n");
	pthread_array = malloc(sizeof(pthread_t) * waiter->max);
	if (pthread_array == NULL)
		return ;
	i = start_philo(philo_array, pthread_array, waiter->max, waiter);
	if (i == waiter->max)
	{
		*waiter->deat_occurred = FALSE;
		waitercycle(waiter);
	}
	join_philo(pthread_array, i);
	printf("philo main end\n");
}
