/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:10:19 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/14 18:35:49 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int				is_reachable(t_roomlist *iter,
		t_roomlist *elem, int min, t_roomlist *route)
{
	if (iter->room->dist_to_start != -1 &&
		iter->room->dist_to_start != MIN_INT &&
		get_cost(iter, elem) != BLOCKED && (min == -1 || min
		> iter->room->dist_to_start) && !contain_room(route, iter))
		return (1);
	return (0);
}

int				is_in_route(t_roomlist *elem, t_roomlist *iter)
{
	if (elem->room->is_route_part == 0 ||
	(elem->prev_in_route->room->is_route_part == 1
	&& iter->room->is_route_part == 0) ||
	(elem->room->link_from_in_to_out->room->index
	== iter->room->index))
		return (1);
	return (0);
}

t_roomlist		*find_next_room(t_roomlist *child,
		t_roomlist *iter, t_roomlist *elem, t_roomlist *route)
{
	int		min;

	child = NULL;
	min = -1;
	iter = elem->room->links->next;
	while (iter != NULL)
	{
		if (is_reachable(iter, elem, min, route))
		{
			if (is_in_route(elem, iter))
			{
				min = iter->room->dist_to_start;
				child = iter;
			}
		}
		iter = iter->next;
	}
	if (child == NULL)
	{
		free_roomlist(route);
		return (NULL);
	}
	add_room_to_head(&route, child->room);
	child->prev_in_route = elem;
	return (child);
}

t_roomlist		*get_shortest_route(t_roomlist *farm)
{
	t_roomlist		*route;
	t_roomlist		*elem;
	t_roomlist		*child;
	t_roomlist		*iter;

	child = NULL;
	iter = NULL;
	route = make_list();
	elem = get_end(farm);
	elem->prev_in_route = NULL;
	add_room(&route, elem->room);
	while (elem->room->start != 1)
	{
		if ((elem = find_next_room(child, iter, elem, route)) == NULL)
			return (NULL);
	}
	return (route);
}
