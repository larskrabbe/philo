/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:46:37 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/24 23:49:58 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	<sys/time.h>


struct timeval
{
	__darwin_time_t         tv_sec;         /* seconds */
	__darwin_suseconds_t    tv_usec;        /* and microseconds */
};
int	gettimeofday(struct timeval *restrict tp, void *restrict tzp);
