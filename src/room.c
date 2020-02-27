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

t_room				*find_room(t_roomlist *rooms, int index)
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

t_room				*find_room_by_name(t_roomlist *rooms, char *name)
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

void				add_new_cost_to(t_roomlist **room, int cost)
{
	(*room)->cost_to = cost;
}
