/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 00:43:55 by amireid           #+#    #+#             */
/*   Updated: 2024/05/22 18:07:37 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initiate_forks(t_fork *forks, long nbr, t_session *session)
{
	int	i;

	i = -1;
	while (++i < nbr)
	{
		forks[i].id_fork = i;
		if (pthread_mutex_init(&forks[i].fork, NULL) != 0)
			error_free("mutex initiate failed", session);
	}
}

static void	more_assigns(t_philo *philo, t_session *session)
{
	philo->time_since_meal = 0;
	philo->die = session->time_to_die;
	philo->eat = session->time_to_eat;
	philo->sleep = session->time_to_sleep;
	philo->target = session->target_meals;
}

static void	initiate_philos(t_session *sessions)
{
	int	i;

	i = -1;
	while (++i < sessions->nbr_philo)
	{
		more_assigns(&sessions->philos[i], sessions);
		sessions->philos[i].id_philo = i + 1;
		sessions->philos[i].time_since_meal = 0;
		if (pthread_mutex_init(&sessions->philos[i].philos_mutex, NULL) != 0)
			error_free("mutex initiate failed", sessions);
		sessions->philos[i].num_meals = 0;
		sessions->philos[i].session = sessions;
		if (sessions->philos[i].id_philo % 2 == 0)
		{
			sessions->philos[i].fork_one = &sessions->forks[i];
			sessions->philos[i].fork_two = &sessions->forks[
				sessions->philos[i].id_philo % sessions->nbr_philo];
		}
		else
		{
			sessions->philos[i].fork_one = &sessions->forks[
				sessions->philos[i].id_philo % sessions->nbr_philo];
			sessions->philos[i].fork_two = &sessions->forks[i];
		}
	}
}

void	initialize_kraken(t_session *session)
{
	session->end_session = false;
	session->flag_start = false;
	session->the_end = false;
	session->forks = malloc(sizeof(t_fork) * session->nbr_philo);
	session->philos = malloc(sizeof(t_philo) * session->nbr_philo);
	if (!session->forks || !session->philos)
		exit_message("memory error");
	initiate_forks(session->forks, session->nbr_philo, session);
	initiate_philos(session);
	if (pthread_mutex_init(&session->session_mutex, NULL) != 0
		|| pthread_mutex_init(&session->writing_mutex, NULL) != 0)
		error_free("mutex initiate failed", session);
}
