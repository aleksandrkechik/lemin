/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:10:19 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/14 18:35:49 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			get_distances(t_roomlist *rooms)
{
	t_roomlist		*end;
	t_roomlist		*start;
	t_roomlist		*checked;
	t_roomlist		*order;

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
