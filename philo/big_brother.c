/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:13:06 by aeid              #+#    #+#             */
/*   Updated: 2024/05/22 18:07:28 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_if_im_over(t_session *session)
{
	bool	result;

	pthread_mutex_lock(&session->end_all);
	result = session->the_end;
	pthread_mutex_unlock(&session->end_all);
	return (result);
}

static long	check_death(t_philo *philo)
{
	long	time_passed;

	pthread_mutex_lock(&philo->philos_mutex);
	time_passed = get_time_micro(philo->session) - philo->start
		- philo->time_since_meal;
	pthread_mutex_unlock(&philo->philos_mutex);
	return (time_passed);
}

void	*big_brother_watch(void *data)
{
	t_philo	*monitor;
	long	time;

	monitor = (t_philo *)data;
	while (!check_if_im_over(monitor->session))
	{
		time = check_death(monitor);
		if (time >= monitor->die)
		{
			writing_bitch(monitor, "died");
			set_mutex(&monitor->session->session_mutex,
				&monitor->session->end_session, true);
			break ;
		}
	}
	return (NULL);
}
