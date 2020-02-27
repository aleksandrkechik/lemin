/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roomlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:36:44 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/14 17:23:18 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_roomlist			*make_list(void)
{
	t_roomlist		*list;

	list = (t_roomlist*)malloc(sizeof(t_roomlist));
	list->next = NULL;
	list->room = NULL;
	return (list);
}

void				add_room(t_roomlist **head, t_room *room)
{
	t_roomlist		*iter;
	t_roomlist		*elem;

	iter = (*head);
	elem = (t_roomlist*)malloc(sizeof(t_roomlist));
	elem->room = room;
	elem->next = NULL;
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = elem;
	iter->next->cost_to = 1;
	iter->next->cost_from = 1;
}

void				add_room_to_head(t_roomlist **head, t_room *room)
{
	t_roomlist		*elem;

	elem = (t_roomlist*)malloc(sizeof(t_roomlist));
	elem->room = room;
	elem->next = (*head)->next;
	(*head)->next = elem;
	(*head)->next->cost_to = 1;
	(*head)->next->cost_from = 1;
}

int					get_length(t_roomlist *list)
{
	int i;

	i = 0;
	list = list->next;
	while (list != NULL)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_roomlist			*get_start(t_roomlist *list)
{
	list = list->next;
	while (list != NULL)
	{
		if (list->room->start == 1)
			return (list);
		list = list->next;
	}
	return (NULL);
}
