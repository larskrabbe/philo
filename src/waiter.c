/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:18:27 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/11/29 22:28:44 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

/**
 * @brief fill all the information inside of the waiter struct
 * 
 * @param waiter contain all the info/pointer to necesarry to run
 * @param input contain all the input information
 * 
 * @return returns 0 if a error occured 
 */
int	fill_waiter_strc(t_waiter *waiter, t_input *input)
{
	waiter->prio_list = malloc(sizeof(int) * input->philosophers);
	if (waiter->prio_list == NULL)
		return (0);
	return (1);
}

/**
 * @brief "calculate" what philosopher can eat or not eat
 * 
 * @param prio_list array containing the priority to eat for the philosopher
 * @param max max value of philo
 * @param philo current philo that want to eat
 */
void	calc_prio(int *prio_list, int max, t_phil *philo)
{
	int	pos;

	pos = 0;
	while (pos <= max)
	{
		if (prio_list[pos] > 0)
			pthread_mutex_unlock();
		pos++;
	}
}

/**
 * @brief main funktion for the waiter process
 * 
 * @param waiter contain all the info/pointer to necesarry to run
 */
void	waiter(t_waiter *waiter)
{
	int	cur_philo;

	while (*waiter->deat_occurred == TRUE)
	{
		cur_philo = 0;
		while (cur_philo < waiter->max)
		{
			calc_prio(waiter->prio_list);
			cur_philo++;
		}
	}
}
