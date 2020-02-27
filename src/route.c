/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   route.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:36:26 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/14 14:12:21 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int				get_route_length(t_roomlist *route)
{
	t_roomlist		*iter;
	int				length;

	if (!route->next)
		return (0);
	iter = route->next;
	length = 0;
	while (iter != NULL)
	{
		length++;
		iter = iter->next;
	}
	return (length - 1);
}

t_routelist		*make_routelist(void)
{
	t_routelist *list;

	list = (t_routelist*)malloc(sizeof(t_routelist));
	list->next = NULL;
	list->route = NULL;
	list->first = NULL;
	list->last = NULL;
	list->ants_moving = 0;
	return (list);
}

void			add_route(t_routelist *list, t_roomlist *route)
{
	t_routelist		*iter;
	t_routelist		*new;

	iter = list;
	new = (t_routelist*)malloc(sizeof(t_routelist));
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = new;
	iter->last_route = 0;
	new->next = NULL;
	new->route = route;
	new->length = get_route_length(route);
	new->first = NULL;
	new->last_route = 1;
	new->ants_moving = 0;
}

int				get_number_of_routes(t_routelist *routes)
{
	int				i;
	t_routelist		*iter;

	i = 0;
	iter = routes;
	while (iter->next != NULL)
	{
		i++;
		iter = iter->next;
	}
	return (i);
}

void			get_routes_info(t_routelist *routes,
		int *longest, int *shortest)
{
	t_routelist		*iter;

	*longest = -1;
	*shortest = -1;
	iter = routes->next;
	while (iter != NULL)
	{
		if (*longest == -1 || *longest < iter->length)
			*longest = iter->length;
		if (*shortest == -1 || *shortest > iter->length)
			*shortest = iter->length;
		iter = iter->next;
	}
}
