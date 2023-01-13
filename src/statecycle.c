/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statecycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 01:51:06 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/12 10:18:11 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

void	sleeping_cycle(t_phil *brain)
{
	milisleep(brain->input->time_to_sleep);
	statemessage(THINKING, brain);
}

void	eating_cycle(t_phil *brain)
{
	milisleep(brain->input->time_to_eat);
	statemessage(SLEEPING, brain);
	pthread_mutex_unlock(brain->l_fork_mutex);
	pthread_mutex_unlock(brain->r_fork_mutex);
	if (brain->death_flag == FALSE)
		sleeping_cycle(brain);
}

int	check_fork_even(t_phil *brain)
{
	pthread_mutex_lock(brain->l_fork_mutex);
	statemessage(TOOK_L_FORK, brain);
	pthread_mutex_lock(brain->r_fork_mutex);
	eatmessage(TOOK_R_FORK, brain);
	return (1);
}

int	check_fork_odd(t_phil *brain)
{
	pthread_mutex_lock(brain->r_fork_mutex);
	statemessage(TOOK_R_FORK, brain);
	pthread_mutex_lock(brain->l_fork_mutex);
	eatmessage(TOOK_L_FORK, brain);
	return (1);
}

void	thinking_cycle(t_phil *brain)
{
	while (wait_until(&brain->input->start_time))
		usleep(100);
	if (brain->input->philosophers % 2 == 1 && brain->name == 3)
		milisleep(brain->input->time_to_eat + 5);
	if (brain->name % 2 == 1)
		milisleep(10);
	statemessage(THINKING, brain);
	if (brain->check_fork(brain) == 1)
		eating_cycle(brain);
	while (brain->death_flag == FALSE)
	{
		if (brain->check_fork(brain) == 1)
			eating_cycle(brain);
		usleep(200);
	}
	pthread_mutex_lock(&brain->input->mutex_arr[end]);
	(*brain->input->end)++;
	pthread_mutex_unlock(&brain->input->mutex_arr[end]);
}
