/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:10:19 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/14 18:35:49 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				check_around2(t_roomlist *room,
		t_roomlist **checked, t_roomlist *rooms)
{
	t_roomlist		*iter;
	int				dist;

	iter = room->room->links->next;
	if (find_room(*checked, room->room->index) != NULL)
		return ;
	while (iter != NULL)
	{
		dist = find_roomlist_elem(room->room->links,
				iter->room->index)->cost_to;
		if (room->room->parent != -1 && find_roomlist_elem(rooms,
				room->room->parent)->room->is_route_part == 0
		&& room->room->is_route_part == 1 && iter->room->is_route_part == 0)
			;
		else if (find_room(*checked, iter->room->index) == NULL &&
			dist != BLOCKED && (iter->room->dist_to_start == -1 ||
			iter->room->dist_to_start > room->room->dist_to_start + dist))
			iter->room->dist_to_start = room->room->dist_to_start + dist;
		iter = iter->next;
	}
	add_room(checked, room->room);
}

t_roomlist			*get_nearest(t_roomlist *node, t_roomlist **checked,
		t_roomlist *checked_children)
{
	int				cost;
	t_roomlist		*iter;
	t_roomlist		*ret;

	ret = NULL;
	cost = -1;
	iter = node->room->links->next;
	while (iter != NULL)
	{
		if (!contain_room(*checked, iter) && (cost == -1 ||
		cost < iter->cost_from) && get_cost(node, iter)
		!= BLOCKED && contain_room(checked_children, iter) == 0)
		{
			cost = iter->cost_from;
			ret = iter;
			add_room(&checked_children, ret->room);
		}
		iter = iter->next;
	}
	if (ret == NULL)
		return (NULL);
	else
		return (ret);
}

void				on_search_finish(t_roomlist *iter,
		t_roomlist *checked, t_roomlist *checked_children)
{
	free(iter);
	free_roomlist(checked);
	free_roomlist(checked_children);
}

int					cant_be_child(t_roomlist *iter,
		t_roomlist *child, t_roomlist *rooms)
{
	if ((iter->room->parent != -1 && (find_roomlist_elem(rooms,
		iter->room->parent)->room->is_route_part == 0
		&& iter->room->is_route_part == 1 && child->room->is_route_part == 0)))
		return (1);
	return (0);
}

void				width_search2(t_roomlist *rooms, t_roomlist *root,
			t_roomlist **checked, t_roomlist *order)
{
	t_roomlist			*iter;
	t_roomlist			*child;
	t_roomlist			*checked_children;

	check_around2(root, checked, rooms);
	add_to_queue(order, root);
	while (order->next != NULL)
	{
		iter = take_from_queue(&order);
		checked_children = make_list();
		if (get_length(rooms) == get_length((*checked)))
			return (on_search_finish(iter, *checked, checked_children));
		while ((child = get_nearest(iter, checked, checked_children)) != NULL)
		{
			if (cant_be_child(iter, child, rooms))
				continue;
			child->room->parent = iter->room->index;
			check_around2(child, checked, rooms);
			add_to_queue(order, child);
		}
		free_roomlist(checked_children);
		free(iter);
	}
	free_roomlist(*checked);
}
