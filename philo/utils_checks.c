/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:43:51 by aeid              #+#    #+#             */
/*   Updated: 2024/05/22 18:07:47 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_if_all_ready(t_session *session)
{
	bool	result;

	pthread_mutex_lock(&session->session_mutex);
	result = session->flag_start;
	pthread_mutex_unlock(&session->session_mutex);
	return (result);
}

bool	check_if_simulation_ended(t_session *session)
{
	bool	result;

	pthread_mutex_lock(&session->session_mutex);
	result = session->end_session;
	pthread_mutex_unlock(&session->session_mutex);
	return (result);
}

void	check_eaten_meals(t_philo *philo)
{
	if (!(philo->num_meals % 2) && philo->id_philo % 2 && philo->num_meals > 0)
		usleep(10);
	if (philo->num_meals % 2 && !(philo->id_philo % 2) && philo->num_meals > 0)
		usleep(10);
}
