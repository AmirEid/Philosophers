/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:33:57 by aeid              #+#    #+#             */
/*   Updated: 2024/05/22 18:12:06 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	initialize_kraken(t_session *session)
{
	sem_unlink("/block_fork");
	sem_unlink("/block_write");
	sem_unlink("/block_control");
	if (session->num_philos == 1)
		return ;
	session->pid = malloc(sizeof(int) * session->num_philos);
	if (!session->pid)
		exit_message(session, "memory error");
	management_open(&session->fork, "/block_fork", session->num_philos,
		session);
	management_open(&session->write, "/block_write", 1, session);
	management_open(&session->control, "/block_control", 1, session);
}

int	main(int argc, char **argv)
{
	t_session	*session;

	session = NULL;
	if (argc == 5 || argc == 6)
	{
		session = malloc(sizeof(t_session));
		if (!session)
			return (0);
		check_n_parse(session, argv, argc);
		initialize_kraken(session);
		philosophical_headache_b(session);
		wait_then_clean(&session);
	}
	else
		exit_message(session, "Wrong input, asshole!");
}
