/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_stuff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:16:27 by hturkatr          #+#    #+#             */
/*   Updated: 2020/01/29 15:50:10 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			print_room_sequence(t_roomlist *list)
{
	list = list->next;
	while (list != NULL)
	{
		printf("%s-", list->room->name);
		list = list->next;
	}
	printf("\n");
}

//void			print_room_links(t_roomlist *list)
//{
//	list = list->next;
//	while (list != NULL)
//	{
//		printf("%s(%d) cost = %d --", list->room->name, list->room->index, list->cost);
//		print_room_sequence(list->room->links);
//		list = list->next;
//	}
//}

void			print_farm(t_roomlist *list)
{
	int farm[30][30];
	int i;
	t_roomlist *iter;
	int j;
	int k;

	j = 0;
	k = 0;

	while (j < 30)
	{
		while (k < 30)
		{
			farm[j][k] = -1;
			k++;
		}
		k = 0;
		j++;
	}

	i = 0;
	iter = list->next;
	while (i < get_length(list))
	{
		farm[iter->room->coord_y][iter->room->coord_x] = iter->room->index;
		i++;
		iter = iter->next;
	}

	j = 0;
	k = 0;
	i = 0;

	iter = list->next;
	while (j < 20)
	{
		while (k < 20)
		{
			if (farm[j][k] == -1)
				printf("  .");
			else
			{
//				if (find_room(list, farm[j][k])->start == 1)
//					printf("S");
//				else if (iter->end == 1)
//					printf("E");
//				else
					printf("%3s", find_room(list, farm[j][k])->name);
				i++;
			}
			k++;
		}
		printf("\n");
		k = 0;
		j++;
	}
}

void			print_dist_to_end(t_roomlist *list)
{
	int farm[30][30];
	int i;
	t_roomlist *iter;
	int j;
	int k;

	j = 0;
	k = 0;

	while (j < 30)
	{
		while (k < 30)
		{
			farm[j][k] = -1;
			k++;
		}
		k = 0;
		j++;
	}

	i = 0;
	iter = list->next;
	while (i < get_length(list))
	{
		farm[iter->room->coord_y][iter->room->coord_x] = iter->room->index;
		i++;
		iter = iter->next;
	}

	j = 0;
	k = 0;
	i = 0;

	iter = list->next;
	while (j < 20)
	{
		while (k < 30)
		{
			if (farm[j][k] == -1)
				printf("  .");
			else
			{
				if (find_room(list, farm[j][k])->end == 1)
					printf("E");
//				else if (iter->end == 1)
//					printf("E");
				else
					printf("%3d", find_room(list, farm[j][k])->dist_to_end);
				i++;
			}
			k++;
		}
		printf("\n");
		k = 0;
		j++;
	}
}

void			print_dist_to_start(t_roomlist *list)
{
	int farm[30][30];
	int i;
	t_roomlist *iter;
	int j;
	int k;

	j = 0;
	k = 0;

	while (j < 30)
	{
		while (k < 30)
		{
			farm[j][k] = -1;
			k++;
		}
		k = 0;
		j++;
	}

	i = 0;
	iter = list->next;
	while (i < get_length(list))
	{
		farm[iter->room->coord_y][iter->room->coord_x] = iter->room->index;
		i++;
		iter = iter->next;
	}

	j = 0;
	k = 0;
	i = 0;

	iter = list->next;
	while (j < 10)
	{
		while (k < 10)
		{
			if (farm[j][k] == -1)
				printf("  .");
			else
			{
				if (find_room(list, farm[j][k])->start == 1)
					printf("  S");
//				else if (iter->end == 1)
//					printf("E");
				else
					printf("%3d", find_room(list, farm[j][k])->dist_to_start);
				i++;
			}
			k++;
		}
		printf("\n");
		k = 0;
		j++;
	}
}

void		print_routes_info(t_routelist *routes)
{
	t_routelist *iter;

	iter = routes->next;
	while (iter != NULL)
	{
		printf("route length = %d, %d moves, %d ants\n", iter->length, iter->moves, iter->ants);
		iter = iter->next;
	}
}

t_roomlist		*get_shortest_route_from_room(t_roomlist *farm, char *name)
{
	t_roomlist		*route;
	t_roomlist		*elem;
	t_roomlist		*child;
	t_roomlist		*iter;
	int				min;

	route = make_list();
//	elem = get_end(farm);
	elem = find_roomlist_elem_by_name(farm, name);

	add_room(&route, elem->room);
//	printf("%d\n", get_room_links(farm, "Wpt0"));
	printf("%s--", elem->room->name);
	while (elem->room->start != 1)
	{
		child = NULL;
		min = -1;
		iter = elem->room->links->next;
		while (iter != NULL)
		{
			if (get_cost(iter, elem) != BLOCKED && (min == -1 || min > iter->room->dist_to_start)  && !contain_room(route, iter))
			{
				min = iter->room->dist_to_start;
				child = iter;
			}
			iter = iter->next;
		}
		if (child == NULL)
		{
			free_roomlist(route);
			return (NULL);
		}
		printf("%s--", child->room->name);
		add_room_to_head(&route, child->room);
		elem = child;
	}
	printf("\n");
	return (route);
}