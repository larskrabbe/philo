/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:53:06 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/08 16:35:09 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

/**
 * @brief allocate a array of mutexarray and initlize them
 * 
 * @param len size of the array
 * 
 */
static pthread_mutex_t	*get_mutex_array(size_t len)
{
	pthread_mutex_t	*ptr;
	size_t			i;

	i = 0;
	//printf("len = %zu\n", len);
	ptr = malloc(sizeof(pthread_mutex_t) * len);
	//printf("mutex array address = %p\n", ptr);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		if (pthread_mutex_init(&ptr[i], NULL))
			return (NULL);
		i++;
	}
	//printf("mutex array address = %p\n", ptr);
	return (ptr);
}

/**
 * @brief create the mutex link between waiter and philos
 * 
 * @param waiter the controll pthread struct
 * @param philo_array a array of philosopher
 */
int	mutex_link(t_phil *philo_array, t_waiter *waiter)
{
	int	i;

	i = 0;
	//printf("in mutex_link\n");
	waiter->request_mutex = get_mutex_array(waiter->max);
	if (waiter->request_mutex == NULL)
		return (0);
	waiter->philo_mutex = get_mutex_array(waiter->max);
	//printf("in mutex_link mutex array address = %p\n", waiter->philo_mutex);
	if (waiter->philo_mutex == NULL)
	{
		free(waiter->request_mutex);
		return (0);
	}
	while (i < waiter->max)
	{
		(philo_array + i)->request_mutex = &waiter->request_mutex[i];
		(philo_array + i)->philo_mutex = &waiter->philo_mutex[i];
		i++;
	}
	//printf("i = %i, waiter->max = %i\n", i, waiter->max);
	return (1);
}
