/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:39:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 14:18:18 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

int	check_input(t_input *input)
{
	if (input->philosophers > 2000 || input->philosophers < 1)
		return (-1);
	if (input->time_to_die > 100000 || input->time_to_die < 60)
		return (-1);
	if (input->time_to_eat > 10000 || input->time_to_eat < 60)
		return (-1);
	if (input->time_to_sleep > 10000 || input->time_to_sleep < 60)
		return (-1);
	if (input->amount_to_eat > 100 || input->amount_to_eat < 60)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_input		input;
	int			death;
	t_waiter	*waiter;
	t_phil		*philo_array;

	death = FALSE;
	// input.deat_occurred = &death;
	printf("\033[0;32m philo start for real\033[0m\n");
	transform_args(&input, argc, argv);
	waiter = create_waiter(input.philosophers);
	if (waiter == NULL)
		return (0);
	if (check_input(&input) < 0)
		printf("invalid input\n");
	else
	{
		philo_array = create_philo(&input);
		if (!mutex_link(philo_array, waiter))
			pthread_main(philo_array, waiter);
		free(philo_array);
	}
	delete_waiter(waiter);
	printf("\033[0;32mphilo end\033[0m\n");
	return (0);
}
