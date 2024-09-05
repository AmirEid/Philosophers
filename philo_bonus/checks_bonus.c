/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:21:53 by aeid              #+#    #+#             */
/*   Updated: 2024/05/22 18:11:58 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_valid_input(t_session *session, char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		exit_message(session, "We don't accept negativity");
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i])
		exit_message(session, "seriously??");
}

static long	ft_atol(char *str)
{
	long	number;
	int		i;

	i = -1;
	number = 0;
	while (str[++i])
		number = (number * 10) + (str[i] - '0');
	return (number);
}

static void	more_checks(t_session *session)
{
	session->num_meals = 0;
	session->pid = NULL;
	session->fork = NULL;
	session->write = NULL;
	session->control = NULL;
	if (session->num_philos == 0)
		exit_message(session, "No philosophers, no wisdom!");
	if (session->num_philos > 200)
		exit_message(session, "Too much wisdom for today!");
	if (session->die < 60000 || session->eat < 60000 || session->sleep < 60000)
		exit_message(session, "What the hell man!, try more than 59ms");
}

void	check_n_parse(t_session *session, char **argv, int argc)
{
	int		i;
	long	str[5];

	i = 0;
	while (argv[++i])
	{
		check_valid_input(session, argv[i]);
		str[i - 1] = ft_atol(argv[i]);
		if (str[i - 1] > INT_MAX)
			exit_message(session, "It is too big, smartass!");
	}
	session->num_philos = str[0];
	session->die = str[1] * 1000;
	session->eat = str[2] * 1000;
	session->sleep = str[3] * 1000;
	if (argc == 6)
		session->target_meals = str[4];
	else
	{
		session->target_meals = -1;
		str[4] = 0;
	}
	session->outcome = 0;
	session->flag = false;
	more_checks(session);
}
