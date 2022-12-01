/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:18:27 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/01 17:23:27 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

/**
 * @brief "calculate" what philosopher can eat or not eat
 * 
 * @param prio_list array containing the priority to eat for the philosopher
 * @param max max value of philo
 * @param philo current philo that want to eat
 */
void	calc_prio(t_waiter *waiter, int pos)
{
	while (pos <= waiter->max)
	{
		if (waiter->prio_list[pos] > 0)
			// pthread_mutex_unlock();
		pos++;
	}
}

/**
 * @brief check each philo if there send a request
 *
 */
void	check_for_request(t_waiter *waiter)
{
	int	i;

	i = 0;
	while (i < waiter->max)
	{
		pthread_mutex_lock(&waiter->request_mutex[i]);
			// check_prio(waiter, i);
		pthread_mutex_unlock(&waiter->request_mutex[i]);
		i++;
	}
}

/**
 * @brief main funktion for the waiter process
 * 
 * @param waiter contain all the info/pointer to necesarry to run
 */
void	waiter(t_waiter *waiter)
{
	// int	cur_philo;

	while (*waiter->deat_occurred == TRUE)
	{
		check_for_request(waiter);
	}
}
