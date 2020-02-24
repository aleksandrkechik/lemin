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

t_routelist		*make_routelist()
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

void			get_routes_info(t_routelist *routes, int *longest, int *shortest)
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

t_routelist		*get_shortest(t_routelist *routes)
{
	t_routelist		*iter;
	int				min;

	min = -1;
	iter = routes->next;
	while (iter != NULL)
	{
		if (min == -1 || min > iter->moves)
			min = iter->moves;
		iter = iter->next;
	}
	iter = routes->next;
	while (iter != NULL)
	{
		if (min == iter->moves)
			return (iter);
		iter = iter->next;
	}
	return (NULL);
}

//previous
//void			bring_balance_to_the_force_not_destroy_it(t_routelist *routes, int ants_remain, int ants_to_route)
//{
//	t_routelist		*iter;
//	int				median;
//
//	int ants_to_move;
//	median = 0;
//	ants_to_move = ants_remain;
//	iter = routes->next;
//	while (iter != NULL)
//	{
//		median += iter->length;
//		iter->moves = iter->length + ants_to_route - 1;
//		iter = iter->next;
//	}
//	median /= get_number_of_routes(routes);
//	median = median + ants_to_route - 1;
////	print_routes_info(routes);
//	int		balanced;
//	balanced = 0;
//	while (balanced == 0)
//	{
//		iter = routes->next;
//		while (iter != NULL)
//		{
//			if (iter->moves > median && iter->moves >= iter->length)
//			{
//				iter->moves--;
//				ants_to_move++;
//			}
//			else if (iter->moves < median)
//			{
//				iter->moves++;
//				ants_to_move--;
//			}
//			else
//				balanced++;
//			if (balanced == get_number_of_routes(routes))
//				break;
//			iter = iter->next;
//		}
//		if (balanced == get_number_of_routes(routes))
//			break;
//		balanced = 0;
//	}
//	while (ants_to_move > 0)
//	{
//		iter = get_shortest(routes);
//		iter->moves++;
//		ants_to_move--;
//	}
//	iter = routes->next;
//	while (iter != NULL)
//	{
//		iter->ants = iter->moves - iter->length + 1;
//		iter = iter->next;
//	}
////	printf("\n");
////	print_routes_info(routes);
//}

t_routelist		*find_longest(t_routelist *routes)
{
	t_routelist		*longest;
	t_routelist		*iter;

	iter = routes->next;
	longest = routes->next;
	while (iter != NULL)
	{
		if (iter->moves > longest->moves && iter->ants > 1)
			longest = iter;
		iter = iter->next;
	}
	return (longest);
}

t_routelist		*find_shortest(t_routelist *routes)
{
	t_routelist		*shortest;
	t_routelist		*iter;

	iter = routes->next;
	shortest = routes->next;
	while (iter != NULL)
	{
		if (iter->moves < shortest->moves)
			shortest = iter;
		iter = iter->next;
	}
	return (shortest);
}
////New
void			bring_balance_to_the_force_not_destroy_it(t_routelist *routes, int ants_remain, int ants_to_route)
{
	t_routelist		*iter;
	t_routelist		*longest;
	t_routelist		*shortest;


	iter = routes->next;
	while (iter != NULL)
	{
		iter->ants = ants_to_route;
		iter->moves = iter->length + ants_to_route;
		iter = iter->next;
	}
	int		balanced = 0;
	longest = find_longest(routes);
	shortest = find_shortest(routes);
	while (balanced == 0)
	{
		if ((longest->moves - shortest->moves == 0 || longest->moves - shortest->moves == 1))
			balanced = 1;
		if (ants_remain > 0)
		{
			shortest->moves++;
			shortest->ants++;
			ants_remain--;
		}
		if (longest->ants > 1)
		{
			longest->moves--;
			longest->ants--;
			ants_remain++;
		}
		longest = find_longest(routes);
		shortest = find_shortest(routes);
	}
	while (ants_remain > 0)
	{
		shortest = find_shortest(routes);
		ants_remain--;
		shortest->moves++;
		shortest->ants++;
	}
}

int				get_moves_total(t_routelist *routes)
{
	t_routelist		*iter;
	int				moves;

	iter = routes->next;
	moves = -1;
	while (iter != NULL)
	{
		if (moves == -1 || moves < iter->moves)
			moves = iter->moves;
		iter = iter->next;
	}
	return (moves);
}

int				count_moves(t_routelist *routes, int ants)
{
	int routes_number;
	int longest;
	int shortest;
	int ants_to_route;
	int ants_remain;
	int moves_total;

	routes_number = get_number_of_routes(routes);
	get_routes_info(routes, &longest, &shortest);
	ants_to_route = ants / routes_number;
	ants_remain = ants % routes_number;

	//COUNT OPTIMAL NUMBER OF ANTS TO EACH ROUTE
//	moves_total = shortest + (ants_to_route - 1);
	//// If routes_number == 2
	//diff = longest - shortest
	//ants to shortest = 1/2 * ants - diff
	//ants to longest = 1/2 *ants + diff

	bring_balance_to_the_force_not_destroy_it(routes, ants_remain, ants_to_route);
	moves_total = get_moves_total(routes);
	return (moves_total);
}


t_routelist		*copy_routelist(t_routelist *list)
{
	t_routelist		*new;
	t_routelist		*iter;
	t_roomlist		*room_iter;
	t_roomlist		*temp;

	new = make_routelist();
	iter = list->next;
	while (iter != NULL)
	{
		temp = make_list();
		room_iter = iter->route->next;
		while (room_iter != NULL)
		{
			add_room(&(temp), room_iter->room);
			room_iter = room_iter->next;
		}
		new->moves = iter->moves;
		new->ants = iter->ants;
		new->length = iter->length;
		iter = iter->next;
		add_route(new, temp);
	}
	return (new);
}

int		check_room_uniqueness(t_routelist *routes)
{
	t_roomlist	*check;

	check = make_list();
	t_routelist		*iter_route;
	t_roomlist		*iter_rooms;
	iter_route = routes->next;
	while (iter_route != NULL)
	{
		iter_rooms = iter_route->route->next;
		while (iter_rooms != NULL)
		{
			if (contain_room(check, iter_rooms) == 1 && iter_rooms->room->start != 1 && iter_rooms->room->end != 1)
				return (0);
			add_room(&check, iter_rooms->room);
			iter_rooms = iter_rooms->next;
		}
		iter_route = iter_route->next;
	}
	printf("OK");
	return (1);
}



