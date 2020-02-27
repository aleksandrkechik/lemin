/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_room.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:38:09 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/15 14:01:19 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int			check_coordinates(t_roomlist *farm, int coord_x, int coord_y)
{
	t_roomlist		*iter;

	iter = farm->next;
	while (iter != NULL)
	{
		if (iter->room->coord_x == coord_x && iter->room->coord_y == coord_y)
			return (0);
		iter = iter->next;
	}
	return (1);
}

void		init_room(t_room *room, int *room_index, int room_status)
{
	if (room_status == -1)
		room->start = 1;
	else if (room_status == 1)
		room->end = 1;
	else
	{
		room->start = 0;
		room->end = 0;
	}
	room->links = make_list();
	room->dist_to_start = -1;
	room->dist_to_end = -1;
	room->index = *room_index;
	room->link_from_in_to_out = NULL;
	room->is_route_part = 0;
	room->parent = -1;
	(*room_index)++;
}

int			put_room_in_farm(t_room *room, int *room_index,
		int room_status, t_roomlist *rooms)
{
	init_room(room, room_index, room_status);
	if (check_coordinates(rooms, room->coord_x, room->coord_y) == 0
		|| find_roomlist_elem_by_name(rooms, room->name) != NULL)
		return (0);
	add_room(&rooms, room);
	return (1);
}

int			get_coords(char *line, int *i, char **temp)
{
	char	*iter;

	(*i) = 0;
	if (line[0] == 'L')
		return (0);
	if (((*temp) = ft_strchr(line, ' ')) == '\0')
		return (0);
	iter = line;
	while (iter != (*temp))
	{
		iter++;
		(*i)++;
	}
	(*temp)++;
	return (1);
}

int			process_room(char *line, t_roomlist *rooms,
						int room_status, int *room_index)
{
	t_room	*room;
	char	*temp;
	int		temp_int;
	int		i;

	room = make_room();
	if (!get_coords(line, &i, &temp))
		return (0);
	room->name = ft_strsub(line, 0, i);
	if (ft_isdigit(temp[0]) && (temp_int = ft_atoi(temp)) >= 0)
	{
		room->coord_x = temp_int;
		temp = ft_strchr(temp, ' ');
		if (temp == NULL)
			return (0);
		temp++;
		if ((ft_isdigit(temp[0]) && (temp_int = ft_atoi(temp)) >= 0))
		{
			room->coord_y = temp_int;
			if (ft_strchr(temp, ' ') == '\0')
				return (put_room_in_farm(room, room_index, room_status, rooms));
		}
	}
	return (0);
}
