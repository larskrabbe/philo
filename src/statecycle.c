/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statecycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 01:51:06 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/27 08:34:10 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

void	milisleep(unsigned int time)
{
	usleep(time * 1000);
}

void	sleeping_cycle(t_phil *brain)
{
	statemessage(SLEEPING, &brain->input->start_time, brain);
	if (brain->input->time_to_sleep > brain->input->time_to_die)
		milisleep(brain->input->time_to_die);
	else
		milisleep(brain->input->time_to_sleep);
	statemessage(THINKING, &brain->input->start_time, brain);
}

void	eating_cycle(t_phil *brain)
{
	statemessage(EATING, &brain->input->start_time, brain);
	milisleep(brain->input->time_to_eat);
	brain->energy = brain->input->time_to_die;
	pthread_mutex_lock(&brain->input->fork_mutex[brain->name]);
	pthread_mutex_lock(&brain->input->fork_mutex[brain->right_fork]);
	brain->input->forks[brain->name] = 0;
	brain->input->forks[brain->right_fork] = 0;
	pthread_mutex_unlock(&brain->input->fork_mutex[brain->name]);
	pthread_mutex_unlock(&brain->input->fork_mutex[brain->right_fork]);
	sleeping_cycle(brain);
}

int	check_fork(t_phil *brain)
{
	int	i;

	i = on_table;
	pthread_mutex_lock(&brain->input->fork_mutex[brain->name]);
	if (brain->input->forks[brain->name] == on_table)
	{
		pthread_mutex_lock(&brain->input->fork_mutex[brain->right_fork]);
		if (brain->input->forks[brain->right_fork] == on_table)
		{
			i = in_hand;
			brain->input->forks[brain->name] = in_hand;
			statemessage(TOOK_FORK, &brain->input->start_time, brain);
			brain->input->forks[brain->right_fork] = in_hand;
			statemessage(TOOK_FORK, &brain->input->start_time, brain);
		}
		pthread_mutex_unlock(&brain->input->fork_mutex[brain->right_fork]);
	}
	pthread_mutex_unlock(&brain->input->fork_mutex[brain->name]);
	return (i);
}

void	thinking_cycle(t_phil *brain)
{
	int	i;

	i = 0;
	statemessage(THINKING, &brain->input->start_time, brain);
	while (brain->energy > 1)
	{
		if (check_fork(brain) == 1)
			eating_cycle(brain);
		i++;
		if (i >= 100)
		{
			brain->energy--;
			i = 0;
		}
	}
	pthread_mutex_lock(&brain->input->mutex_arr[print_check]);
	pthread_mutex_lock(&brain->input->mutex_arr[death_check]);
	if (*brain->input->deat_occurred == FALSE)
	{
		*brain->input->deat_occurred = TRUE;
		printf("%li %i %s\n", get_time_stamp(&brain->input->start_time), brain->name, DEAD);
		exit(0);
	}
	pthread_mutex_unlock(&brain->input->mutex_arr[death_check]);
	pthread_mutex_unlock(&brain->input->mutex_arr[print_check]);
}
