/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:12:37 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/02 22:13:01 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

void	print_strct(t_input *input)
{
	printf("%i\n", input->philosophers);
	printf("%i\n", input->time_to_die);
	printf("%i\n", input->time_to_eat);
	printf("%i\n", input->time_to_sleep);
	printf("%i\n", input->amount_to_eat);
	fflush(stdout);
}
