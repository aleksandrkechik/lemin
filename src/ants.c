/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:11:29 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/15 14:02:34 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		move_ant(t_ant *ant, t_routelist *route)
{
	if (ant->at_end == 0)
	{
		ant->location = ant->location->next;
		printf("L%d-%s", ant->number, ant->location->room->name);
		if (ant->location->room->end == 1)
		{
			ant->at_end = 1;
		}
		route->ants_moving--;
		if (route->ants_moving == 0)
			return (0);
		else
			return (1);
	}
	return (2);
}

int		get_mumber_of_ants_to_move(t_routelist *route)
{
	t_ant	*anterator;
	int		ants_to_move;

	ants_to_move = 0;
	anterator = route->first;
	while (anterator != NULL)
	{
		if (anterator->at_end != 1)
			ants_to_move++;
		anterator = anterator->next;
	}
	return (ants_to_move);
}

int		need_space(t_routelist *route)
{
	t_routelist		*iter;

	iter = route->next;
	while (iter != NULL)
	{
		if (iter->ants_moving != 0)
		{
			printf(" ");
			return (0);
		}
		iter = iter->next;
	}
	return (0);
}

void	move_all_ants(t_routelist *route)
{
	t_ant		*anterator;
	int			ret;

	anterator = route->first;
	while (anterator != NULL)
	{
		if (anterator->at_end != 1)
		{
			ret = move_ant(anterator, route);
			if (route->ants_moving == 0)
				need_space(route);
			else
				printf(" ");
		}
		anterator = anterator->next;
	}
	route->ants_moving = get_mumber_of_ants_to_move(route);
}

void	give_birth_to_the_ant(int number, t_routelist *route)
{
	t_ant	*ant;
	t_ant	*anterator;

	ant = (t_ant*)malloc(sizeof(t_ant));
	ant->number = number;
	ant->location = (route)->route->next;
	ant->at_end = 0;
	anterator = route->first;
	if (anterator == NULL)
	{
		route->first = ant;
		route->last = ant;
		route->first->next = NULL;
	}
	else
	{
		while (anterator->next != NULL)
			anterator = anterator->next;
		anterator->next = ant;
		ant->next = NULL;
		route->last = ant;
	}
	route->ants_moving++;
}
