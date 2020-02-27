/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 14:07:06 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/14 14:04:25 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	modify_graph(t_roomlist *farm)
{
	t_roomlist	*current_room;
	t_roomlist	*link_to;

	current_room = farm->next;
	while (current_room != NULL)
	{
		link_to = current_room->room->links->next;
		while (link_to != NULL)
		{
			link_to = link_to->next;
		}
		current_room = current_room->next;
	}
}

void	exclude_route(t_roomlist *farm, t_roomlist *route)
{
	t_roomlist		*current;
	t_roomlist		*next;

	current = route->next;
	next = current->next;
	while (current->next != NULL)
	{
		modify_link_cost(find_roomlist_elem(farm, current->room->index),
				find_roomlist_elem(farm, next->room->index), BLOCKED);
		current = current->next;
		next = next->next;
	}
}

void	freeing_parse(t_roomlist *iter, int intersection_2, t_roomlist **temp_2)
{
	while (iter->room->index != intersection_2)
	{
		(*temp_2) = iter->next;
		free(iter);
		iter = (*temp_2);
	}
	(*temp_2) = iter->next;
	free(iter);
}

void	handle_intersection(t_roomlist *shortest_1, t_roomlist *shortest_2,
		int intersection_1, int intersection_2)
{
	t_roomlist		*iter;
	t_roomlist		*int_1;
	t_roomlist		*int_2;
	t_roomlist		*temp_1;
	t_roomlist		*temp_2;

	iter = shortest_1->next;
	while (iter->room->index != intersection_1)
		iter = iter->next;
	int_1 = iter;
	iter = iter->next;
	freeing_parse(iter, intersection_2, &temp_2);
	iter = shortest_2->next;
	while (iter->room->index != intersection_2)
		iter = iter->next;
	int_2 = iter;
	iter = iter->next;
	freeing_parse(iter, intersection_1, &temp_1);
	int_1->next = temp_1;
	int_2->next = temp_2;
}

void	check_intersections(t_routelist *routes)
{
	t_routelist	*first;
	t_routelist	*second;

	if ((first = routes->next) == NULL
	|| (second = first->next) == NULL)
		return ;
	while (first->next != NULL)
	{
		while (second != NULL)
		{
			have_intersection(first->route, second->route);
			second = second->next;
		}
		first = first->next;
		second = first->next;
	}
}
