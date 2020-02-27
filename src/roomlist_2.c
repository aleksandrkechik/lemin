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

int						contain_room(t_roomlist *list, t_roomlist *room)
{
	if (list->room == NULL)
		list = list->next;
	while (list != NULL)
	{
		if (list->room->index == room->room->index)
			return (1);
		list = list->next;
	}
	return (0);
}

void					add_to_queue(t_roomlist *queue, t_roomlist *elem)
{
	t_roomlist	*new;
	t_roomlist	*iter;

	if (queue->next == NULL)
		iter = queue;
	else
	{
		iter = queue;
		while (iter->next != NULL)
			iter = iter->next;
	}
	new = (t_roomlist*)malloc(sizeof(t_roomlist));
	new->room = elem->room;
	new->next = NULL;
	iter->next = new;
}

t_roomlist				*take_from_queue(t_roomlist **queue)
{
	t_roomlist *elem;

	elem = (*queue)->next;
	(*queue)->next = (*queue)->next->next;
	return (elem);
}

t_roomlist				*get_end(t_roomlist *list)
{
	list = list->next;
	while (list != NULL)
	{
		if (list->room->end == 1)
			return (list);
		list = list->next;
	}
	return (NULL);
}
