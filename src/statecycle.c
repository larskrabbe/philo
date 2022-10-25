/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statecycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 01:51:06 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/25 07:04:41 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

void	milisleep(unsigned int time)
{
	usleep(time * 1000);
}

void	sleeping_cycle(t_philosophor *brain)
{
	statemessage(brain->name, SLEEPING, &brain->input->start_time);
	if (brain->input->time_to_sleep > brain->input->time_to_die)
		milisleep(brain->input->time_to_die);
	else
		milisleep(brain->input->time_to_sleep);
	statemessage(brain->name, THINKING, &brain->input->start_time);
}

void	eating_cycle(t_philosophor *brain)
{
	statemessage(brain->name, TOOK_FORK, &brain->input->start_time);
	statemessage(brain->name, TOOK_FORK, &brain->input->start_time);
	statemessage(brain->name, EATING, &brain->input->start_time);
	milisleep(brain->input->time_to_eat);
	brain->energy = brain->input->time_to_die;
	pthread_mutex_lock(brain->input->mutex);
	brain->input->forks[brain->name] = 0;
	brain->input->forks[brain->name + 1] = 0;
	pthread_mutex_unlock(brain->input->mutex);
	sleeping_cycle(brain);
}


void	thinking_cycle(t_philosophor *brain)
{
	int	i;

	i = 0;
	statemessage(brain->name, THINKING, &brain->input->start_time);
	while (brain->energy > 1)
	{
		if (brain->input->forks[brain->name] == 0 && \
		brain->input->forks[brain->name + 1] == 0)
		{
			pthread_mutex_lock(brain->input->mutex);
			brain->input->forks[brain->name] = 1;
			brain->input->forks[brain->name + 1] = 1;
			pthread_mutex_unlock(brain->input->mutex);
			eating_cycle(brain);
		}
		usleep(10);
		i++;
		if (i >= 100)
		{
			brain->energy--;
			i = 0;
		}
	}
	statemessage(brain->name, DEAD, &brain->input->start_time);
}
