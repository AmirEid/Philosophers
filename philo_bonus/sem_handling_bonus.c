/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_handling_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:17:12 by amireid           #+#    #+#             */
/*   Updated: 2024/05/22 18:12:12 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	semaphore_error_managment(t_session *session, const char *type)
{
	if (errno == EACCES)
		printf("%s EACCES error\n", type);
	else if (errno == EEXIST)
		printf("%s EEXIST error\n", type);
	else if (errno == EINTR)
		printf("%s EINTR error\n", type);
	else if (errno == EMFILE)
		printf("%s EMFILE error\n", type);
	else if (errno == ENFILE)
		printf("%s ENFILE error", type);
	else if (errno == ENOENT)
		printf("%s ENOENT error\n", type);
	else if (errno == ENOSPC)
		printf("%s ENOSPC error\n", type);
	else if (errno == EINVAL)
		printf("%s EINVAL error\n", type);
	else if (errno == EAGAIN)
		printf("%s EAGAIN error\n", type);
	else if (errno == EDEADLK)
		printf("%s EDEADLK error\n", type);
	else
		printf("%s ENAMETOOLONG error\n", type);
	error_free(session);
	exit(EXIT_FAILURE);
}

void	management_unlink(const char *name, t_session *ses)
{
	int	status;

	status = 0;
	status = sem_unlink(name);
	if (status == -1)
		semaphore_error_managment(ses, "UNLINK");
}

void	ft_management(t_sem_code code, sem_t **semaphore, t_session *ses)
{
	int	status;

	status = 0;
	if (code == POST)
	{
		status = sem_post(*semaphore);
		if (status == -1)
			semaphore_error_managment(ses, "POST");
	}
	else if (code == WAIT)
	{
		status = sem_wait(*semaphore);
		if (status == -1)
			semaphore_error_managment(ses, "WAIT");
	}
	else if (code == CLOSE)
	{
		status = sem_close(*semaphore);
		if (status == -1)
			semaphore_error_managment(ses, "CLOSE");
	}
}

void	management_open(sem_t **semaphore, const char *name, int value,
		t_session *ses)
{
	*semaphore = sem_open(name, O_CREAT, 0644, value);
	if (*semaphore == SEM_FAILED)
		semaphore_error_managment(ses, "OPEN");
}
