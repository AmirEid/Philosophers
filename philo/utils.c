/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 02:37:43 by amireid           #+#    #+#             */
/*   Updated: 2024/05/22 18:07:51 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_micro(t_session *session)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		error_free("Error occurred with time", session);
	return ((time.tv_sec * 1000000) + (time.tv_usec));
}

void	ft_usleep(t_session *session, long time, t_philo *philo, char *message)
{
	long	start;

	if (check_if_simulation_ended(session))
		return ;
	start = get_time_micro(session);
	while (get_time_micro(session) - start < time)
		;
	writing_bitch(philo, message);
}

void	exit_message(char *error_message)
{
	printf("%s\n", error_message);
	exit(EXIT_FAILURE);
}

void	error_free(char *error_message, t_session *session)
{
	printf("%s\n", error_message);
	cleaning_lady(session);
	exit(EXIT_FAILURE);
}

void	cleaning_lady(t_session *session)
{
	int	i;

	i = -1;
	while (++i < session->nbr_philo)
	{
		pthread_mutex_destroy(&session->forks[i].fork);
		pthread_mutex_destroy(&session->philos[i].philos_mutex);
	}
	pthread_mutex_destroy(&session->writing_mutex);
	pthread_mutex_destroy(&session->session_mutex);
	if (session->nbr_philo != 1)
		pthread_mutex_destroy(&session->end_all);
	free(session->forks);
	free(session->philos);
}
