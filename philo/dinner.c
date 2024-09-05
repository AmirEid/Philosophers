/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:05:21 by amireid           #+#    #+#             */
/*   Updated: 2024/07/09 19:16:33 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	gay_philo(t_session *session)
{
	session->start = get_time_micro(session);
	session->philos->start = session->start;
	if (pthread_create(&session->philos[0].id_thread, NULL, mr_lonely,
			&session->philos[0]) != 0)
		error_free("thread creation failed", session);
}

static void	thinking(t_philo *philo)
{
	writing_bitch(philo, "is thinking");
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_one->fork);
	writing_bitch(philo, "has taken a fork");
	pthread_mutex_lock(&philo->fork_two->fork);
	writing_bitch(philo, "has taken a fork");
	get_time_safe(&philo->philos_mutex, &philo->time_since_meal, philo->session,
			philo->start);
	philo->num_meals++;
	ft_usleep(philo->session, philo->eat, philo, "is eating");
	pthread_mutex_unlock(&philo->fork_one->fork);
	pthread_mutex_unlock(&philo->fork_two->fork);
}

static void	*start_session(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!check_if_all_ready(philo->session))
		usleep(1);
	if (pthread_create(&philo->big_brother, NULL, big_brother_watch,
			philo) != 0)
		error_free("thread creation failed", philo->session);
	while (!check_if_simulation_ended(philo->session))
	{
		eating(philo);
		if (philo->target > 0 && philo->num_meals == philo->target)
		{
			set_mutex(&philo->session->end_all, &philo->session->the_end, true);
			break ;
		}
		ft_usleep(philo->session, philo->sleep, philo, "is sleeping");
		thinking(philo);
		check_eaten_meals(philo);
	}
	if (pthread_join(philo->big_brother, NULL) != 0)
		error_free("Joining threads failed", philo->session);
	return (NULL);
}

void	philosophical_headache(t_session *session)
{
	int	i;

	i = -1;
	if (session->target_meals == 0)
		return ;
	if (pthread_mutex_init(&session->end_all, NULL) != 0)
		error_free("mutex initiate failed", session);
	if (session->nbr_philo == 1)
		gay_philo(session);
	else
	{
		session->start = get_time_micro(session);
		while (++i < session->nbr_philo)
		{
			if (pthread_create(&session->philos[i].id_thread, NULL,
					start_session, &session->philos[i]) != 0)
				error_free("thread creation failed", session);
			session->philos[i].start = session->start;
		}
	}
	set_mutex(&session->session_mutex, &session->flag_start, true);
	i = -1;
	while (++i < session->nbr_philo)
		join_thread(&session->philos[i].id_thread, session);
}
