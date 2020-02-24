/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:41:34 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/13 15:28:27 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void	free_roomlist(t_roomlist *list)
{
	t_roomlist *iter;

	iter = list->next;
	while (iter != NULL)
	{
		free(iter);
		iter = iter->next;
	}
	free(list);
}

void	free_routelist(t_routelist *list)
{
	t_routelist *iter;

	iter = list->next;
	while (iter != NULL)
	{
		free_roomlist(iter->route);
		free_ants(iter);
		free(iter);
		iter = iter->next;
	}
	free(list);
}

void	free_farm(t_roomlist *farm)
{
	t_roomlist *iter;

	iter = farm->next;
	while (iter != NULL)
	{
		if (iter->room != NULL) {
			if (iter->room->links != NULL)
				free_roomlist((iter->room->links));
			if (iter->room->name != NULL)
			{
				free(iter->room->name);
			}
			free(iter->room);
		}
		free(iter);
		iter = iter->next;
	}
	free(farm);
}

void	free_ants(t_routelist *route)
{
	t_ant	*anterator;

	anterator = route->first;
	while (anterator != NULL)
	{
		free(anterator);
		anterator = anterator->next;
	}
}

void	free_route_copy(t_routelist *list)
{
	t_routelist *iter;

	iter = list->next;
	while (iter != NULL)
	{
		free_roomlist(iter->route);
		free_ants(iter);
		free(iter);
		iter = iter->next;
	}
	free(list);
}