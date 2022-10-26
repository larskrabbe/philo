/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe < lkrabbe@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:45:46 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/26 13:35:31 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

pthread_mutex_t	*get_mutex_array(size_t len)
{
	pthread_mutex_t	*ptr;
	size_t			i;

	i = 0;
	ptr = malloc(sizeof(pthread_mutex_t) * len);
	if (ptr == NULL)
		return (0);//free error
	while (i < len)
	{
		if (pthread_mutex_init(&ptr[i], NULL))
			return (0);//free error
		i++;
	}
	return (ptr);
}

int	simple_atoi(char *str)
{
	long	num;
	int		i;

	i = 0;
	num = 0;
	while(str[i] <= '9' && str[i] >= '0')
	{
		num = num + str[i] + '0';
		i++;
		if (num > INT32_MAX)
			return (-1);
	}
	return (num);
}

int	is_white_space(int a)
{
	if (a == ' ' || a == '\n' || a == '\t')
		return (1);
	return (0);
}

char	*get_next_arg(int argc,char *argv[])
{
	static	char	*ptr = NULL;	
	static	int		argcount = 0;
	int				i;

	i = 0;
	if (argcount > argc)
		return(NULL);
	if (ptr == NULL)
		ptr = argv[argcount];
	else
		while (ptr[argcount][i] != '0' && !is_white_space(ptr[argcount][i]))
			i++;
	while (ptr[argcount][i] != '0' && is_white_space(*ptr[argcount][i]))
		i++;
	if (*ptr != '/0')
		return(ptr);
	if( argcount < argc)
		argcount++;
	ptr = NULL;
	return(get_next_arg(argc, argv));
}	

void parsing(int argc,char *argv[])
{
	printf(">%s\n" , get_next_arg(argc, argv));
	printf(">%s\n" , get_next_arg(argc, argv));
	printf(">%s\n" , get_next_arg(argc, argv));
	printf(">%s\n" , get_next_arg(argc, argv));
	printf(">%s\n" , get_next_arg(argc, argv));		
}

void	transform_args(t_input *input)
{
	input->philosophers = 200;
	input->time_to_die = 300;
	input->time_to_eat = 100;
	input->time_to_sleep = 100;
	input->amount_to_eat = 20;
	input->forks = malloc(sizeof(int) * input->philosophers);
	memset(input->forks, 0, input->philosophers);
	gettimeofday(&input->start_time, NULL);
	input->fork_mutex = get_mutex_array(input->philosophers);
	pthread_mutex_init(&input->mutex, NULL);
}
