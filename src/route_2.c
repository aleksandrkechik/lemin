/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:36:26 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/14 14:12:21 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_routelist		*find_longest(t_routelist *routes)
{
	t_routelist		*longest;
	t_routelist		*iter;

	iter = routes->next;
	longest = routes->next;
	while (iter != NULL)
	{
		if (iter->moves > longest->moves && iter->ants > 1)
			longest = iter;
		iter = iter->next;
	}
	return (longest);
}

t_routelist		*find_shortest(t_routelist *routes)
{
	t_routelist		*shortest;
	t_routelist		*iter;

	iter = routes->next;
	shortest = routes->next;
	while (iter != NULL)
	{
		if (iter->moves < shortest->moves)
			shortest = iter;
		iter = iter->next;
	}
	return (shortest);
}

int				get_moves_total(t_routelist *routes)
{
	t_routelist		*iter;
	int				moves;

	iter = routes->next;
	moves = -1;
	while (iter != NULL)
	{
		if (moves == -1 || moves < iter->moves)
			moves = iter->moves;
		iter = iter->next;
	}
	return (moves);
}

int				count_moves(t_routelist *routes, int ants)
{
	int		longest;
	int		shortest;
	int		ants_to_route;
	int		ants_remain;
	int		moves_total;

	get_routes_info(routes, &longest, &shortest);
	ants_to_route = ants / get_number_of_routes(routes);
	ants_remain = ants % get_number_of_routes(routes);
	bring_balance_to_the_force_not_destroy_it(routes,
								ants_remain, ants_to_route);
	moves_total = get_moves_total(routes);
	return (moves_total);
}

t_routelist		*copy_routelist(t_routelist *list)
{
	t_routelist		*new;
	t_routelist		*iter;
	t_roomlist		*room_iter;
	t_roomlist		*temp;

	new = make_routelist();
	iter = list->next;
	while (iter != NULL)
	{
		temp = make_list();
		room_iter = iter->route->next;
		while (room_iter != NULL)
		{
			add_room(&(temp), room_iter->room);
			room_iter = room_iter->next;
		}
		new->moves = iter->moves;
		new->ants = iter->ants;
		new->length = iter->length;
		iter = iter->next;
		add_route(new, temp);
	}
	return (new);
}
