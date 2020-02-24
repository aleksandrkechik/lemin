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

t_roomlist		*make_list()
{
	t_roomlist		*list;

	list = (t_roomlist*)malloc(sizeof(t_roomlist));
	list->next = NULL;
	list->room = NULL;
	return (list);
}

void			add_room(t_roomlist **head, t_room *room)
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

void			add_room_to_head(t_roomlist **head, t_room *room)
{
	t_roomlist		*elem;

//	iter = (*head);
	elem = (t_roomlist*)malloc(sizeof(t_roomlist));
	elem->room = room;
	elem->next = (*head)->next;
//	while (iter->next != NULL)
//		iter = iter->next;
	(*head)->next = elem;
	(*head)->next->cost_to = 1;
	(*head)->next->cost_from = 1;
}

int				get_length(t_roomlist *list)
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

//t_room			*get_end(t_roomlist *list)
//{
//	list = list->next;
//	while (list != NULL)
//	{
//		if (list->room->end == 1)
//			return (list->room);
//		list = list->next;
//	}
//	return (NULL);
//}

t_roomlist			*get_end(t_roomlist *list)
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

int					contain_room(t_roomlist *list, t_roomlist *room)
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

////previous version
//void				add_to_queue(t_roomlist **queue, t_roomlist *elem)
//{
//	t_roomlist	*new;
//
//	new = (t_roomlist*)malloc(sizeof(t_roomlist));
////	new = elem;
//	new->room = elem->room;
////	new->cost = elem->cost;
//	new->next = (*queue)->next;
//	(*queue)->next = new;
//}

////new_version
void				add_to_queue(t_roomlist *queue, t_roomlist *elem)
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
//	new = elem;
	new->room = elem->room;
//	new->cost = elem->cost;
	new->next = NULL;
	iter->next = new;
}

t_roomlist			*take_from_queue(t_roomlist **queue)
{
	t_roomlist *elem;

	elem = (*queue)->next;
	(*queue)->next = (*queue)->next->next;
	return (elem);
}

t_roomlist			*copy_roomlist(t_roomlist *list)
{
	t_roomlist *new;
	t_roomlist *iter;

	new = make_list();
	iter = list->next;
	while (iter != NULL)
	{
		add_room(&new, iter->room);
		iter = iter->next;
	}
	return (new);
}

void			make_backup_links(t_roomlist *farm)
{
	t_roomlist		*iter;

	iter = farm->next;
	while (iter != NULL)
	{
		iter->room->links_backup = copy_roomlist(iter->room->links);
		iter = iter->next;
	}
}

void		pop_link(t_roomlist *from, t_roomlist *to)
{
	t_roomlist	*iter;

	iter = from->room->links;
	while (iter != NULL)
	{
		if (iter->next != NULL && iter->next->room == to->room)
		{
			iter->next = iter->next->next;
//			find_roomlist_elem(from, iter->room->index)->next = iter->next->next;
//			free(to);
		}
		iter = iter->next;
	}
}