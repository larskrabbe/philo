/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:39:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/27 05:37:25 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"
/**
 * need to  check the values for :
 *! number_of_philosophers
 *! time_to_die
 *! time_to_eat
 *! time_to_sleep
 *! number_of_times_each_philosopher_must_eat (optional argument)
 */

void	print_strct(t_input *input)
{
	printf("%i\n", input->philosophers);
	printf("%i\n", input->time_to_die);
	printf("%i\n", input->time_to_eat);
	printf("%i\n", input->time_to_sleep);
	printf("%i\n", input->amount_to_eat);
	fflush(stdout);
}


int	check_input(t_input *input)
{
	if (input->philosophers > 200 || input->philosophers < 1)
		return (-1);
	if (input->time_to_die > 1000 || input->time_to_die < 1)
		return (-1);
	if (input->time_to_eat > 1000 || input->time_to_eat < 1)
		return (-1);
	if (input->time_to_sleep > 1000 || input->time_to_sleep < 1)
		return (-1);
	if (input->amount_to_eat > 1000 || input->amount_to_eat < 1)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_input	input;

	printf("\033[0;32m philo start for real\033[0m\n");
	transform_args(&input, argc, argv);
	if (check_input(&input) < 0)
		printf("invalid input\n");
	else
		create_philo(&input, 1);
	printf("\033[0;32mphilo end\033[0m\n");
	return (0);
}
