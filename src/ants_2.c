/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:11:29 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/15 14:02:34 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		show_stopper(t_routelist *routes)
{
	t_routelist *iter;

	iter = routes->next;
	while (iter != NULL)
	{
		if (iter->moves > 0)
			return (0);
		iter = iter->next;
	}
	return (1);
}

void	ant_birth_cycle(t_routelist *routes, int *ants_moved)
{
	t_routelist		*iter;

	iter = routes->next;
	while (iter != NULL)
	{
		if (iter->moves > 0)
		{
			if (iter->ants >= 1)
			{
				give_birth_to_the_ant(*ants_moved, iter);
				(*ants_moved)++;
				iter->ants--;
			}
		}
		iter = iter->next;
	}
}

void	process_ant_migration(t_routelist *routes)
{
	t_routelist		*iter;
	int				ants_moved;

	ants_moved = 1;
	iter = routes->next;
	get_number_of_routes(routes);
	while (1)
	{
		ant_birth_cycle(routes, &ants_moved);
		iter = routes->next;
		while (iter != NULL)
		{
			if (iter->last == NULL || iter->last->at_end != 1)
			{
				move_all_ants(iter);
			}
			iter->moves--;
			iter = iter->next;
		}
		iter = routes->next;
		if (show_stopper(routes) == 1)
			break ;
		printf("\n");
	}
}
