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

t_roomlist			*reverse_list(t_roomlist *list)
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

t_roomlist			*find_intersection_end(t_roomlist *shortest_1,
								t_roomlist *shortest_2)
{
	t_roomlist *end;
	t_roomlist *iter_1;
	t_roomlist *iter_2;

	end = NULL;
	iter_1 = shortest_1->next;
	iter_2 = shortest_2->next;
	while (iter_1 != NULL && iter_2 != NULL &&
		iter_1->room->index == iter_2->room->index)
	{
		end = iter_1;
		iter_1 = iter_1->next;
		iter_2 = iter_2->next;
	}
	return (end);
}

void				check_intersection(t_roomlist *shortest_1,
		t_roomlist *shortest_2,
		t_roomlist *first, t_roomlist *second)
{
	t_roomlist *int_start;
	t_roomlist *int_end;

	int_start = first;
	int_end = find_intersection_end(first, second);
	if (int_end != NULL)
		handle_intersection(shortest_1, shortest_2,
							int_start->room->index, int_end->room->index);
}

void				have_intersection(t_roomlist *shortest_1,
		t_roomlist *shortest_2)
{
	t_roomlist *first;
	t_roomlist *reversed;
	t_roomlist *second;

	reversed = reverse_list(shortest_2);
	first = shortest_1->next;
	second = reversed->next;
	while (first != NULL)
	{
		while (second != NULL)
		{
			if (first->room->index == second->room->index)
				check_intersection(shortest_1, shortest_2, first, second);
			second = second->next;
		}
		second = reversed->next;
		first = first->next;
	}
	free_roomlist(reversed);
}
