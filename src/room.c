/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:43:32 by hturkatr          #+#    #+#             */
/*   Updated: 2020/01/22 17:44:07 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_room			*find_room(t_roomlist *rooms, int index)
{
	t_roomlist *iter;

	iter = rooms->next;
	while (iter != NULL)
	{
		if (iter->room->index == index)
			return (iter->room);
		iter = iter->next;
	}
	return (NULL);
}

t_roomlist			*find_roomlist_elem(t_roomlist *rooms, int index)
{
	t_roomlist *iter;

	iter = rooms;
	if (iter->room == NULL)
		iter = iter->next;
	while (iter != NULL)
	{
		if (iter->room->index == index)
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

t_room			*find_room_by_name(t_roomlist *rooms, char *name)
{
	t_roomlist *iter;

	iter = rooms->next;
	while (iter != NULL)
	{
		if (ft_strequ(iter->room->name, name) == 1)
			return (iter->room);
		iter = iter->next;
	}
	return (NULL);
}

t_roomlist			*find_roomlist_elem_by_name(t_roomlist *rooms, char *name)
{
	t_roomlist *iter;

	iter = rooms->next;
	while (iter != NULL)
	{
		if (ft_strequ(iter->room->name, name) == 1)
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

void		add_new_cost_to(t_roomlist **room, int cost)
{
	(*room)->cost_to = cost;
}

void		add_new_cost_from(t_roomlist **room, int cost)
{
	(*room)->cost_from = cost;
}

void		modify_link_cost(t_roomlist *from, t_roomlist *to, int new_cost)
{
	t_roomlist		*temp;
	t_roomlist		*iter;

	iter = from->room->links->next;
//	from->room->links = from->room->links->next;
	while (iter->room->index != to->room->index)
		iter = iter->next;
	add_new_cost_to(&(iter), new_cost);
	temp = find_roomlist_elem(to->room->links, from->room->index);
	add_new_cost_from(&temp, new_cost);
}

int			get_cost(t_roomlist *from, t_roomlist *to)
{
	t_roomlist		*iter;
	int				cost;

//	if (from->room->links->room == NULL)
//		from->room->links = from->room->links->next;
//	while (from->room->links && from->room->links->room->index != to->room->index)
//		from->room->links = from->room->links->next;
	iter = from->room->links;
	if (iter->room == NULL)
		iter = iter->next;
	while (iter->room->index != to->room->index)
		iter = iter->next;
//
	cost = iter->cost_to;
	return (cost);
//	return (from->room->links->cost);
}

int			get_cost_from(t_roomlist *from, t_roomlist *to)
{
	t_roomlist		*iter;
	int				cost;

//	if (from->room->links->room == NULL)
//		from->room->links = from->room->links->next;
//	while (from->room->links && from->room->links->room->index != to->room->index)
//		from->room->links = from->room->links->next;
	iter = from->room->links;
	if (iter->room == NULL)
		iter = iter->next;
	while (iter->room->index != to->room->index)
		iter = iter->next;
//
	cost = iter->cost_from;
	return (cost);
//	return (from->room->links->cost);
}

int			get_startroom_links(t_roomlist *farm)
{
	t_roomlist *start;

	start = get_start(farm);
	return (get_route_length(start->room->links) + 1);
}