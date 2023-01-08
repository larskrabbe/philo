/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:18:27 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/08 21:43:41 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

int	right_philo(int max, int i)
{
	if (i == max - 1)
		return (0);
	return (i + 1);
}

int	left_philo(int max, int i)
{
	if (i == 0)
		return (max - 1);
	return (i - 1);
}


int	check_forks(t_waiter *waiter, int i)
{
	if (waiter->request_copy[i] != 1)
		return (1);
	if (waiter->request_copy[right_philo(waiter->max, i)] != 1)
		return (2);
	if (waiter->request_copy[left_philo(waiter->max, i)] != 1)
		return (3);
	if (waiter->prio_list[i] > waiter->prio_list[right_philo(waiter->max, i)])
		return (4);
	if (waiter->prio_list[i] > waiter->prio_list[left_philo(waiter->max, i)])
		return (5);
	waiter->request_copy[i] = 2;
	waiter->prio_list[i]++;
	printf("i = %i prio = %i\n", i, waiter->prio_list[i]);
	return (6);
}

/**
 * @brief "calculate" what philosopher can eat or not eat
 * 
 * @param prio_list array containing the priority to eat for the philosopher
 * @param max max value of philo
 * @param philo current philo that want to eat
 */
void	calc_prio(t_waiter *waiter)
{
	int	i;

	i = 0;
	while (i < waiter->max)
	{
		// check_forks(waiter, i);
		printf("%i->%ip>%i |", i, check_forks(waiter, i),waiter->prio_list[i]);
		i++;
	}
		printf("\n");
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
		waiter->request_copy[i] = waiter->request_list[i];
		// printf("%i\n", waiter->request_copy[i]);
		pthread_mutex_unlock(&waiter->request_mutex[i]);
		i++;
	}
}

void	send_replie(t_waiter *waiter)
{
	int	i;

	i = 0;
	while (i < waiter->max)
	{
		//printf("r%i->%i=%i \n", i, waiter->request_list[i], waiter->request_list[i]);
		pthread_mutex_lock(&waiter->request_mutex[i]);
		waiter->request_list[i] = waiter->request_copy[i];
		//printf("%i\n", waiter->request_list[i]);
		if (waiter->request_list[i] == 2)
		{
			printf("unlocks %i request = %i \n", i, waiter->request_list[i]);
			waiter->request_list[i] = 0;
			pthread_mutex_unlock(&waiter->philo_mutex[i]);
		}
			// printf("%i\n", waiter->request_copy[i]);
		pthread_mutex_unlock(&waiter->request_mutex[i]);
		i++;
	}
}


/**
 * @brief main funktion for the waiter process
 * 
 * @param waiter contain all the info/pointer to necesarry to run
 */
void	waitercycle(t_waiter *waiter)
{
	// int	cur_philo;

	while (*waiter->deat_occurred == FALSE)
	{
		// printf("check\n");
		check_for_request(waiter);
		// printf("calc\n");
		calc_prio(waiter);
		// printf("send\n");
		send_replie(waiter);
	}
}
