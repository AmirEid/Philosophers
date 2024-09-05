/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:33:57 by aeid              #+#    #+#             */
/*   Updated: 2024/05/22 18:07:41 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_session	session;

	if (argc == 5 || argc == 6)
	{
		check_n_parse(&session, argv, argc);
		initialize_kraken(&session);
		philosophical_headache(&session);
		cleaning_lady(&session);
	}
	else
		exit_message("Wrong input, asshole!");
}
