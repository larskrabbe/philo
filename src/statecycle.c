/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statecycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 01:51:06 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/11/06 21:25:44 by lkrabbe          ###   ########.fr       */
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

void	milisleep(unsigned int time)
{
	// long long			dif_time;
	// struct timeval		start_time;
	// struct timeval		current_time;

	// gettimeofday(&current_time, NULL);
	// gettimeofday(&start_time, NULL);
	// dif_time = timeval_to_ll(&start_time, &current_time);
	// while (time - dif_time > 100)
	// {
	// 	usleep(dif_time * 0.8);
	// 	dif_time = timeval_to_ll(&start_time, &current_time);
	// }
		usleep(time * 0.8);
}

void	sleeping_cycle(t_phil *brain)
{
	statemessage(SLEEPING, brain);
	if (brain->input->time_to_sleep > brain->input->time_to_die)
		milisleep(brain->input->time_to_die);
	else
		milisleep(brain->input->time_to_sleep);
	statemessage(THINKING, brain);
}

void	eating_cycle(t_phil *brain)
{
	statemessage(EATING, brain);
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
			statemessage(TOOK_L_FORK, brain);
			brain->input->forks[brain->right_fork] = in_hand;
			statemessage(TOOK_R_FORK, brain);
		}
		pthread_mutex_unlock(&brain->input->fork_mutex[brain->right_fork]);
	}
	pthread_mutex_unlock(&brain->input->fork_mutex[brain->name]);
	return (i);
}

void	thinking_cycle(t_phil *brain)
{
	if (brain->death_flag == TRUE)
		return ;
	else if (check_fork(brain) == 1)
		eating_cycle(brain);
	else
		statemessage(THINKING, brain);
	while (get_time_stamp(&brain->death_time) < 0)
	{
		if (check_fork(brain) == 1)
			eating_cycle(brain);
		else
		{
			milisleep(1);
			brain->energy--;
		}
	}
	pthread_mutex_lock(&brain->input->mutex_arr[death_check]);
	if (*brain->input->deat_occurred == FALSE)
	{
		*brain->input->deat_occurred = TRUE;
		printf("%li %i %s\n", get_time_stamp(&brain->input->start_time), brain->name, DEAD);
	}
	pthread_mutex_unlock(&brain->input->mutex_arr[death_check]);
}
