/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe < lkrabbe@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:39:00 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/26 13:32:12 by lkrabbe          ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	//t_input	input;
	parsing(argc, argv);
	// transform_args(&input);
	// printf("\033[0;32m philo start\033[0m\n");
	// create_philo(&input, 1);
	// printf("\033[0;32mphilo end\033[0m\n");
	return (0);
}
