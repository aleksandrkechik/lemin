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

# define IN_TREE 1
# define REVERSE_TO_TREE -1
# define OUT_OF_TREE 0
# define DISABLED 2

//// HUGE FUCKUP LIES HERE!!!!!
int		is_in_shortest_tree(t_roomlist *from, t_roomlist *to)
{
	int				new_cost;

	if (get_cost(from, to) == BLOCKED)
	{
//		printf("\nLink from %s to %s is blocked", from->room->name, to->room->name);
//		modify_link_cost(from, to, BLOCKED);
		return (DISABLED);
	}
	else if (from->room->dist_to_start < to->room->dist_to_start)
	{

//		new_cost = get_cost(from, to) - to->room->dist_to_start + from->room->dist_to_start;
		modify_link_cost(from, to, 0);
		return (IN_TREE);
	}
	else if (from->room->dist_to_start > to->room->dist_to_start)
	{
		new_cost = get_cost(from, to) - to->room->dist_to_start + from->room->dist_to_start;
		modify_link_cost(from, to, new_cost);
		return (OUT_OF_TREE);
	}
	return (0);
}

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
//			is_in_shortest_tree(current_room, link_to);
			link_to = link_to->next;
		}
		current_room = current_room->next;
	}
}

//// OLD VERSION
//void	exclude_route(t_roomlist *farm, t_roomlist *route)
//{
//	t_roomlist		*current;
//	t_roomlist		*next;
//
//	current = route->next;
//	next = current->next;
//	while (current->next != NULL)
//	{
////		printf("deleting link from %s to %s\n", current->room->name, next->room->name);
//		modify_link_cost(find_roomlist_elem(farm, current->room->index), find_roomlist_elem(farm, next->room->index), BLOCKED);
//		current = current->next;
//		next = next->next;
//	}
//}

////NEW VERSION
void	exclude_route(t_roomlist *farm, t_roomlist *route)
{
	t_roomlist		*current;
	t_roomlist		*next;
	t_roomlist		*iter;

	current = route->next;
	next = current->next;
	while (current->next != NULL)
	{
//		printf("deleting link from %s to %s\n", current->room->name, next->room->name);
		modify_link_cost(find_roomlist_elem(farm, current->room->index), find_roomlist_elem(farm, next->room->index), BLOCKED);
		iter = next->room->links->next;
//		while (iter != NULL)
//		{
//			if (iter->room->index != current->room->index && iter->room->end != 1 && iter->room->start != 1)
//				modify_link_cost(find_roomlist_elem(farm, next->room->index), find_roomlist_elem(farm, iter->room->index), BLOCKED);
//			iter = iter->next;
//		}
		current = current->next;
		next = next->next;
	}
}

void	reinclude_route(t_roomlist *farm, t_roomlist *route)
{
	t_roomlist		*current;
	t_roomlist		*next;

	current = route->next;
	next = current->next;
	while (current->next != NULL)
	{
//		printf("deleting link from %s to %s\n", current->room->name, next->room->name);
		modify_link_cost(find_roomlist_elem(farm, current->room->index), find_roomlist_elem(farm, next->room->index), 1);
		current = current->next;
		next = next->next;
	}
}

void	handle_intersection(t_roomlist *shortest_1, t_roomlist *shortest_2, t_roomlist *intersection_1, t_roomlist *intersection_2)
{
	t_roomlist *iter;
	t_roomlist *iter_2;
	t_roomlist *temp;
	t_roomlist *temp_2;


	iter = shortest_1->next;
	iter_2 = shortest_2->next;


	while (iter->next->room->index != intersection_1->room->index)
		iter = iter->next;
	temp_2 = iter;
	while (temp_2->room->index != intersection_2->room->index)
		temp_2 = temp_2->next;
	while (iter_2->room->index != intersection_2->room->index)
		iter_2 = iter_2->next;
	temp = iter_2;
	while (iter_2->room->index != intersection_1->room->index)
		iter_2 = iter_2->next;
	iter->next->next = iter_2->next;
	temp->next = temp_2->next;
}

void	include_routes(t_roomlist *farm, t_routelist *routes)
{
	t_routelist *iter;

	iter = routes->next;
	while (iter != NULL)
	{
		reinclude_route(farm, iter->route);
		iter = iter->next;
	}
}

void	exclude_routes(t_roomlist *farm, t_routelist *routes)
{
	t_routelist *iter;

	iter = routes->next;
	while (iter != NULL)
	{
		exclude_route(farm, iter->route);
		iter = iter->next;
	}
}

void	check_intersections(t_routelist *routes)
{
	t_routelist	*first;
	t_routelist	*second;

	if ((first = routes->next) == NULL || (second = first->next)== NULL)
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

t_roomlist	*reverse_list(t_roomlist *list)
{
	t_roomlist	*new;
	t_roomlist	*iter;

	new = make_list();
	iter = list->next;
	while (iter != NULL)
	{
		add_room_to_head(&new, iter->room);
		iter = iter->next;
	}
	return (new);
}

t_roomlist	*find_intersection_end(t_roomlist *shortest_1, t_roomlist *shortest_2)
{
	t_roomlist *end;
	t_roomlist *iter_1;
	t_roomlist *iter_2;

	end = NULL;

	iter_1 = shortest_1->next;
	iter_2 = shortest_2->next;
	while (iter_1 != NULL && iter_2 != NULL && iter_1->room->index == iter_2->room->index)
	{
		end = iter_1;
		iter_1 = iter_1->next;
		iter_2 = iter_2->next;
	}
	return (end);
}

void	have_intersection(t_roomlist *shortest_1, t_roomlist *shortest_2)
{
	t_roomlist *first;
	t_roomlist *reversed;
	t_roomlist *second;
	t_roomlist *int_start;
	t_roomlist *int_end;


	reversed = reverse_list(shortest_2);
	first = shortest_1->next;
	second = reversed->next;
	while (first != NULL)
	{
		while (second != NULL)
		{
			if (first->room->index == second->room->index)
			{
				int_start = first;
				int_end = find_intersection_end(first, second);
				if (int_end != NULL)
					handle_intersection(shortest_1, shortest_2, int_start, int_end);
			}
			second = second->next;
		}
		second = reversed->next;
		first = first->next;
	}
	free_roomlist(reversed);
}