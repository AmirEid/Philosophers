/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:18:35 by aeid              #+#    #+#             */
/*   Updated: 2024/05/22 18:07:54 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_mutex(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

void	*mr_lonely(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!check_if_all_ready(philo->session))
		usleep(1);
	if (pthread_create(&philo->big_brother, NULL, big_brother_watch,
			philo) != 0)
		error_free("thread creation failed", philo->session);
	pthread_mutex_lock(&philo->fork_one->fork);
	writing_bitch(philo, "has taken a fork");
	get_time_safe(&philo->philos_mutex, &philo->time_since_meal, philo->session,
		philo->start);
	pthread_mutex_unlock(&philo->fork_one->fork);
	if (pthread_join(philo->big_brother, NULL) != 0)
		error_free("Joining threads failed", philo->session);
	return (NULL);
}

void	writing_bitch(t_philo *philo, char *message)
{
	long	time;

	if (check_if_simulation_ended(philo->session))
		return ;
	time = (get_time_micro(philo->session) - philo->start) / 1000;
	pthread_mutex_lock(&philo->session->writing_mutex);
	printf("%-5ld %d %s\n", time, philo->id_philo, message);
	pthread_mutex_unlock(&philo->session->writing_mutex);
}

void	get_time_safe(pthread_mutex_t *mutex, long *current, t_session *session,
		long start)
{
	pthread_mutex_lock(mutex);
	*current = get_time_micro(session) - start;
	pthread_mutex_unlock(mutex);
}

void	join_thread(pthread_t *thread, t_session *session)
{
	if (pthread_join(*thread, NULL) != 0)
		error_free("Joining threads failed", session);
}
