/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:48:55 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/02 19:45:41 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

/**
 * @brief allocate the prio_list to store the current prio for  the philo
 * 
 * @param waiter contain all the info/pointer to necesarry to run
 * @param input contain all the input information
 * 
 * @return returns 0 if a error occured
 */
static int	create_prio_list(t_waiter *waiter, int philo_count)
{
	int	i;

	i = 0;
	waiter->prio_list = malloc(sizeof(int) * philo_count);
	if (waiter->prio_list == NULL)
		return (0);
	while (i < philo_count)
	{
			waiter->prio_list[i] = 0;
			i++;
	}
	return (1);
}

/**
 * @brief allocate the request list, to link the philos to the waiter-process
 * 
 * @param waiter contain all the info/pointer to necesarry to run
 * @param input contain all the input information
 * 
 * @return returns 0 if a error occured 
 */
static int	create_request_list(t_waiter *waiter, int philo_count)
{
	int	i;

	i = 0;
	waiter->request_list = malloc(sizeof(int) * philo_count);
	if (waiter->request_list == NULL)
		return (0);
	while (i < philo_count)
	{
		waiter->request_list[i] = 1;
		i++;
	}
	return (1);
}

/**
 * @brief allocat space for the waiter structur
 * 
 * @param philo_count waiter structer is depending on the amount of philosopher
 * 
 * @return the address of the struture or null if allocation failed
 */
t_waiter	*create_waiter(int philo_count)
{
	t_waiter	*waiter;

	if (philo_count < 1)
		return (NULL);
	waiter = malloc(sizeof(t_waiter));
	if (create_prio_list(waiter, philo_count) == 0)
	{
		free(waiter);
		return (NULL);
	}
	if (create_request_list(waiter, philo_count) == 0)
	{
		free(waiter->prio_list);
		free(waiter);
		return (NULL);
	}
	return (waiter);
}

/**
 * @brief free the whole  waiter structur 
 * 
 */
void	delete_waiter(t_waiter *waiter)
{
	free(waiter->request_list);
	free(waiter->prio_list);
	free(waiter);
}
