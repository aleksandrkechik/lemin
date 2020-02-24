/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links_from_in_to_out_and_route_parts.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 17:53:10 by hturkatr          #+#    #+#             */
/*   Updated: 2020/01/29 18:36:43 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		make_links_from_in_to_out(t_roomlist *route)
{
	t_roomlist		*iter;

	iter = route->next;
	while (iter->next != NULL)
	{
		iter->room->link_from_in_to_out = iter->next;
		if (iter->room->end != 1 && iter->room->start != 1)
			iter->room->is_route_part = 1;
		iter = iter->next;
	}
}

void		clean_links_from_in_to_out(t_roomlist *route)
{
	t_roomlist		*iter;

	iter = route->next;
	while (iter->next != NULL)
	{
		iter->next->room->link_from_in_to_out = NULL;
		if (iter->room->end != 1 && iter->room->start != 1)
			iter->room->is_route_part = 0;
		iter = iter->next;
	}
}

void		clean_links_routes(t_routelist *routes)
{
	t_routelist		*iter;

	iter = routes->next;
	while (iter != NULL)
	{
		clean_links_from_in_to_out(iter->route);
		iter = iter->next;
	}
}

void		make_links_routes(t_routelist *routes)
{
	t_routelist		*iter;

	iter = routes->next;
	while (iter != NULL)
	{
		make_links_from_in_to_out(iter->route);
		iter = iter->next;
	}
}