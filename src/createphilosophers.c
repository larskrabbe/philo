/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createphilosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:58:05 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/09 21:25:05 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

int	wait_until(struct timeval *time)
{
	if (get_time_stamp(time) < 0)
		return (1);
	else
		return (0);
}

void	*lifecycle(void *param)
{
	t_phil	*ptr;

	ptr = param;
	thinking_cycle(param);
	return (NULL);
}

void	philo_input(t_input *input, t_phil *brain, int count)
{
	brain->input = input;
	brain->name = count;
	brain->death_flag = FALSE;
	if (brain->name == input->philosophers)
		brain->right_fork = 1;
	else
		brain->right_fork = count + 1;
	brain->start_time = input->start_time;
	if (brain->name % 2 == 1)
		brain->check_fork = &check_fork_odd;
	else
		brain->check_fork = &check_fork_even;
	brain->energy = input->time_to_die;
}

void	create_philo(t_input *input, int count)
{
	pthread_t		pthread;
	t_phil			*brain;

	if (count <= input->philosophers)
	{
		brain = malloc(sizeof(t_phil));
		if (brain == NULL)
			return ;// error
		philo_input(input, brain, count);
		count++;
		pthread_create(&pthread, NULL, &lifecycle, brain);
		create_philo(input, count);
		if (pthread_join(pthread, NULL) != 0)
			printf("join error\n");
		free(brain);
	}
}
