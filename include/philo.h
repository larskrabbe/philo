/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:39:36 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/08 20:09:30 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//?-----------------THE_INCLUDES---------------?//

# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	<sys/time.h>
# include	<pthread.h>

//?------------------THE_DEFINES---------------?//

# define TOOK_L_FORK "has taken a the left fork"
# define TOOK_R_FORK "has taken a the right fork"
# define EATING  "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"
# ifndef FALSE
#  define FALSE 0
# endif
# ifndef TRUE
#  define TRUE 1
# endif
# ifndef INT32_MAX
#  define INT32_MAX 2147483647
# endif
//?-------------------THE_ENUMS----------------?//

typedef enum e_state{
	thinking = 1,
	sleeping = 2,
	eating = 3,
	dead = 4,
}t_state;

/**
 * @brief The diffrent mutexlocks that arent for forks
 * 
 *! @note last_lock needs to be at the lost position \
 *! its like a counter for the locks 
 *! its needed to malloc the correct size for the array of mutexes
 */
typedef enum e_mutex_locks{
	start_check = 0,
	death_check,
	print_check,
	last_lock,
}t_mutex_locks;

typedef enum e_philoprio{
	can_eat = 0,
	can_not_eat = 1,
}t_philoprio;

//?------------------THE_STRUCTS---------------?//
/**
 * @brief contain all the input from the arguments 
 * so each thread can read it form anywhere
 * 
 */
typedef struct s_input
{
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				amount_to_eat;
	struct timeval	start_time;
}t_input;


/**
 * @brief structer for all the information inside of the waiter process
 * 
 */
typedef struct s_waiter
{
	pthread_mutex_t	*request_mutex;
	pthread_mutex_t	*philo_mutex;
	int				*request_list;
	int				*request_copy;
	int				*prio_list;
	int				*deat_occurred;
	int				max;
}t_waiter;

/**
 * @brief structur for each thread to  get the start information
 * 
 */
typedef struct s_phil{
	t_input			input;
	int				name;
	pthread_mutex_t	*philo_mutex;
	pthread_mutex_t	*request_mutex;
	int				*request;
	int				state;
	int				death_occured;
}t_phil;

//?-----------------THE_PROTOTYPS--------------?//
//TODO
void		statemessage(char *str, t_phil *brain);
void		transform_args(t_input *input, int argc, char *argv[]);
//
t_phil		*create_philo(t_input *input);

void		thinking_cycle(t_phil *brain);
char		*get_next_arg(int argc, char *argv[]);

int			is_white_space(int a);

//+------------philo_setup.c-------------+//

t_phil		*create_philo(t_input *input);
int			start_philo(t_phil *philo_array, pthread_t *pthread_array, int max, t_waiter *waiter);
int			join_philo(pthread_t *pthread_array, int max);

//+--------------waiter.c------------------+//

void		calc_prio(t_waiter *waiter);
void		check_for_request(t_waiter *waiter);
void		waitercycle(t_waiter *waiter);

//+-----------waiter_setup.c--------------+//

t_waiter	*create_waiter(int philo_count);
void		delete_waiter(t_waiter *waiter);

//+-----------time_utils.c--------------+//

long		get_time_stamp(struct timeval *start_time);
void		wait_until(struct timeval *time);
void		time_minus_mili(struct timeval *time, suseconds_t sub);
void		time_plus_mili(struct timeval *time, suseconds_t sub);
void		milisleep(unsigned int time);

//+-------------utiles.c---------------+//

void		print_input_strct(t_input *input);
void		pthread_main(t_phil *philo_array, t_waiter *waiter);
void		print_waiter_info(t_waiter *waiter);

//+-------------statecycle.c------------+//

void		*philocycle(void *param);

//+------------mutex.c---------------+//

int			mutex_link(t_phil *philo_array, t_waiter *waiter);

#endif