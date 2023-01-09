/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statecycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 01:51:06 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/09 21:31:54 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

long long	timeval_to_ll(struct timeval *start, struct timeval *end)
{
	long long	time;

	time = 0;
	time += (start->tv_sec - end->tv_sec * 1000000);
	if (start->tv_usec < end->tv_usec)
	{
		time -= 1000000;
	}
	time += (start->tv_usec - end->tv_usec);
	return (time);
}

void	milisleep(long long time)
{
	struct timeval	timestamp;

	// printf("sleep => %lli\n", time);
	gettimeofday(&timestamp, NULL);
	time_plus_mili(&timestamp, time * 1000);
	while (wait_until(&timestamp))
	{
		usleep(100);
	}
}

void	sleeping_cycle(t_phil *brain)
{
	if (brain->input->time_to_sleep > brain->input->time_to_die)
	{
		milisleep(brain->input->time_to_die);
	}
	else
		milisleep(brain->input->time_to_sleep);
	statemessage(THINKING, brain);
}

void	eating_cycle(t_phil *brain)
{
	statemessage(EATING, brain);
	milisleep(brain->input->time_to_eat);
	// brain->energy = brain->input->time_to_die;
	statemessage(SLEEPING, brain);
	pthread_mutex_unlock(&brain->input->fork_mutex[brain->name]);
	pthread_mutex_unlock(&brain->input->fork_mutex[brain->right_fork]);
	sleeping_cycle(brain);
}



int	check_fork_even(t_phil *brain)
{
	// pre death check
	pthread_mutex_lock(&brain->input->fork_mutex[brain->name]);
	// pre death check
	pthread_mutex_lock(&brain->input->fork_mutex[brain->right_fork]);
	statemessage(TOOK_L_FORK, brain);
	statemessage(TOOK_R_FORK, brain);
	return (1);
}

int	check_fork_odd(t_phil *brain)
{
	// pre death check
	pthread_mutex_lock(&brain->input->fork_mutex[brain->right_fork]);
	// pre death check
	pthread_mutex_lock(&brain->input->fork_mutex[brain->name]);
	statemessage(TOOK_L_FORK, brain);
	statemessage(TOOK_R_FORK, brain);
	return (1);
}

void	death_change(t_phil *brain)
{
	pthread_mutex_lock(&brain->input->mutex_arr[death_check]);
	if (*brain->input->deat_occurred == FALSE)
	{
		*brain->input->deat_occurred = TRUE;
		printf("%li %i %s\n", get_time_stamp(&brain->input->start_time), brain->name, DEAD);
	}
	pthread_mutex_unlock(&brain->input->mutex_arr[death_check]);
}

void	thinking_cycle(t_phil *brain)
{
	while (wait_until(&brain->input->start_time))
		usleep(100);
	if (brain->name % 2 == 0)
	{
		if (brain->check_fork(brain) == 1)
			eating_cycle(brain);
		else
		{
			printf("ERROR");
			exit(1);
		}
	}
	else
		statemessage(THINKING, brain);
	while (brain->death_flag == FALSE)
	{
		if (brain->check_fork(brain) == 1)
			eating_cycle(brain);
	}
	//death_change(brain);
}
