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
	int				ret;

	iter = route->next;
	ret = 1;
	while (iter != NULL)
	{
		if (iter->ants_moving != 0)
		{
			printf (" ");
			return (0);
		}
		iter = iter->next;
	}
//	printf("\n");
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

int	show_stopper(t_routelist *routes)
{
	t_routelist *iter;

	iter = routes->next;
	while (iter != NULL)
	{
		if (iter->moves > 0)
			return (0);
		iter = iter->next;
	}
	return (1);
}

////ТУТ ВСЕ ПОМЕНЯТЬ
int		need_newline(t_routelist *route)
{
	if (route->last_route == 1)
		return (1);
	if (route->next != NULL && route->next->first != NULL && route->next->last != NULL && route->next->last->at_end == 1)
		return (1);
	return (0);
}

//////BACKUP
//void	process_ant_migration(t_routelist *routes)
//{
//	t_routelist		*iter;
//	int				ants_moved;
//
//	ants_moved = 1;
//	iter = routes->next;
//	get_number_of_routes(routes);
//	while (1)
//	{
//		while (iter != NULL)
//		{
//			if (iter->moves > 0)
//			{
//				if (iter->ants >= 1)
//				{
//					give_birth_to_the_ant(ants_moved, iter);
//					ants_moved++;
//					iter->ants--;
//				}
//				if (iter->last == NULL || iter->last->at_end != 1)
//				{
//					move_all_ants(iter);
////					if (iter->last != NULL && iter->last->at_end == 0)
////					if (iter->last_route == 1 && iter->last->at_end == 0)
////					if (need_newline(iter))
////						printf ("\n");
//				}
//				iter->moves--;
//			}
//			iter = iter->next;
//		}
//		iter = routes->next;
//		if (show_stopper(routes) == 1)
//			break;
//	}
////    printf ("\n");
//}

//////NEW
void	process_ant_migration(t_routelist *routes)
{
	t_routelist		*iter;
	int				ants_moved;

	ants_moved = 1;
	iter = routes->next;
	get_number_of_routes(routes);
	while (1) {
		while (iter != NULL) {
			if (iter->moves > 0) {
				if (iter->ants >= 1) {
					give_birth_to_the_ant(ants_moved, iter);
					ants_moved++;
					iter->ants--;
				}
			}
			iter = iter->next;
		}
		iter = routes->next;
		while (iter != NULL) {
			if (iter->last == NULL || iter->last->at_end != 1)
			{
				move_all_ants(iter);
			}
			iter->moves--;
			iter = iter->next;
		}
		iter = routes->next;
		if (show_stopper(routes) == 1)
			break;
		printf("\n");
	}
}