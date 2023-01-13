/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:39:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/12 09:32:45 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

int	check_input(t_input *input)
{
	if (input->philosophers > 200 || input->philosophers < 0)
		return (-1);
	if (input->time_to_die < 60)
		return (-1);
	if (input->time_to_eat < 60)
		return (-1);
	if (input->time_to_sleep < 60)
		return (-1);
	return (0);
}

void	free_all(t_input *input)
{
	int	i;

	i = 0;
	free(input->death_check);
	while (i < input->philosophers)
	{
		pthread_mutex_destroy(&input->fork_mutex[i]);
		i++;
	}
	free(input->fork_mutex);
	i = 0;
	while (i < last_lock)
	{
		pthread_mutex_destroy(&input->mutex_arr[i]);
		i++;
	}
	free(input->mutex_arr);
}

int	main(int argc, char *argv[])
{
	t_input	input;
	int		death;
	int		end;

	end = 0;
	input.end = &end;
	death = FALSE;
	input.deat_occurred = &death;
	if (transform_args(&input, argc, argv) != 0)
		return (0);
	if (input.philosophers != 1)
		setup(&input, 0);
	else
		dinner_for_one(&input);
	free_all(&input);
	return (0);
}
