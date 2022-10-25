/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:39:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/25 04:07:58 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"
/**
 * args
 *! number_of_philosophers
 *! time_to_die
 *! time_to_eat
 *! time_to_sleep
 *! number_of_times_each_philosopher_must_eat (optional argument)
 */

int	main(void)
{
	t_input	input;

	transform_args(&input);
	printf("\033[0;32m philo start\033[0m\n");
	create_philo(&input, 1);
	printf("\033[0;32mphilo end\033[0m\n");
	return (0);
}
