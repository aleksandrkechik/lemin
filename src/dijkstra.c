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

int		check_blocked(t_roomlist *room, t_roomlist *iter)
{
	if (get_cost(room, iter) == 1000)
	{
//		printf("BLOCKED LINK!!!!\n");
		return (1);
	}
	else
		return (0);
}

void	check_around2(t_roomlist *room, t_roomlist **checked, t_roomlist *rooms)
{
	t_roomlist		*iter;
	int				dist;

	iter = room->room->links->next;
	if (find_room(*checked, room->room->index) != NULL)
		return ;
	while (iter != NULL)
	{
		dist = find_roomlist_elem(room->room->links, iter->room->index)->cost_to;
		if (room->room->parent != -1 && find_roomlist_elem(rooms, room->room->parent)->room->is_route_part == 0
		&& room->room->is_route_part == 1 && iter->room->is_route_part == 0)
			;
		else if (find_room(*checked, iter->room->index) == NULL && dist != BLOCKED &&
		(iter->room->dist_to_start == -1 || iter->room->dist_to_start > room->room->dist_to_start + dist))
			iter->room->dist_to_start = room->room->dist_to_start + dist;
		iter = iter->next;
	}

	add_room(checked, room->room);
}

t_roomlist	*get_nearest(t_roomlist *node, t_roomlist **checked, t_roomlist *checked_children)
{
	int				cost;
	int				index;
	t_roomlist		*iter;
	t_roomlist		*ret;

	ret = NULL;
	cost = -1;
	index = -1;
	iter = node->room->links->next;
	while (iter != NULL)
	{
		if (!contain_room(*checked, iter) && (cost == -1 || cost < iter->cost_from) && get_cost(node, iter) != BLOCKED && contain_room(checked_children, iter) == 0)
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

void	width_search2(t_roomlist *rooms, t_roomlist *root, t_roomlist **checked, t_roomlist *order)
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
		{
			free(iter);
			free_roomlist(*checked);
			return ;
		}
		while ((child = get_nearest(iter, checked, checked_children)) != NULL)
		{
			if ((iter->room->parent != -1 && (find_roomlist_elem(rooms, iter->room->parent)->room->is_route_part == 0
											  && iter->room->is_route_part == 1 && child->room->is_route_part == 0)))
			{
				continue;
			}
			child->room->parent = iter->room->index;
			check_around2(child, checked, rooms);
			add_to_queue(order, child);
		}
		free_roomlist(checked_children);
		free(iter);
	}
	free_roomlist(*checked);
}

////WRONG!!!!!!!!!!
int				compare_with_previous_routes(t_roomlist *current, t_roomlist *prev, t_routelist *routes)
{
	t_roomlist		*temp;
	t_routelist		*route_iter;
	int				ret;

	if (prev->room->end == 1 || prev->room->start == 1 || current->room->end == 1 || current->room->start == 1)
		return (1);
	ret = 1;
	route_iter = routes->next;
	while (route_iter != NULL)
	{
		if ((temp = find_roomlist_elem(route_iter->route, current->room->index)) != NULL)
		{
			if (temp->next->room->index != prev->room->index)
				ret = 0;
		}
		route_iter = route_iter->next;
	}
	return (ret);
}

t_roomlist		*get_shortest_route(t_roomlist *farm)
{
	t_roomlist		*route;
	t_roomlist		*elem;
	t_roomlist		*child;
	t_roomlist		*iter;
	t_roomlist		*prev;
	int				min;
	int				came_from_in_link;

	route = make_list();
	elem = get_end(farm);

	printf("\n%s-", elem->room->name);
	prev = NULL;
	came_from_in_link = 0;
	add_room(&route, elem->room);
	while (elem->room->start != 1)
	{
		child = NULL;
		min = -1;
		iter = elem->room->links->next;
		while (iter != NULL)
		{
			if (iter->room->dist_to_start != -1 && iter->room->dist_to_start != MIN_INT && get_cost(iter, elem) != BLOCKED && (min == -1 || min > iter->room->dist_to_start)  && !contain_room(route, iter))
			{
				if (elem->room->is_route_part == 0 || (prev->room->is_route_part == 1 && iter->room->is_route_part == 0)
				|| (elem->room->link_from_in_to_out->room->index == iter->room->index))
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
			printf("\n");
			return (NULL);
		}
		printf("%s(%d)-", child->room->name, child->room->dist_to_start);
		add_room_to_head(&route, child->room);
		prev = elem;
		elem = child;
	}
	printf("\n");
	return (route);
}

void			get_distances(t_roomlist *rooms)
{
	t_roomlist		*end;
	t_roomlist		*start;
	t_roomlist		*checked;
	t_roomlist		*order;

////Making backup links

	end = get_end(rooms);
	end->room->dist_to_end = 0;
	start = get_start(rooms);
	start->room->dist_to_start = 0;
	checked = make_list();
	order = make_list();
	width_search2(rooms, start, &checked, order);
	free_roomlist(order);
}

void			clean_distances(t_roomlist *rooms)
{
	t_roomlist		*iter;

	iter = rooms->next;
	while (iter != NULL)
	{
		if (iter->room->start == 1)
			iter->room->dist_to_start = 0;
		else
			iter->room->dist_to_start = -1;
		iter = iter->next;
	}
}