/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:38:09 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/15 14:01:19 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int		check_name(char *name)
{
	name++;
//	const char	*ext = ft_strstr(name, ".map");
//
//	if(ext == NULL)
//		return (0);
//	if(ft_strlen(ext) == 4)
//		return (1);
//	return (0);
	return (1);
}

int		handle_first_line(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
		{
			return (0);
		}
		i++;
	}
	return (ft_atoi(line));
}

int		make_link(t_roomlist *rooms, char *room_1, char *room_2)
{
	t_room *first_room;
	t_room *second_room;

	if ((first_room = find_room_by_name(rooms, room_1)) == NULL || (second_room = find_room_by_name(rooms, room_2)) == NULL ||
	find_room_by_name(first_room->links, room_2) != NULL || find_room_by_name(second_room->links, room_1) != NULL)
		return (0);
	add_room(&(first_room->links), second_room);
	add_room(&(second_room->links), first_room);
	return (1);
}

int		arr_size(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

int		process_link(char *line, t_roomlist *rooms)
{
	char	**names;
	int		ret;

	ret = -1;
	names = ft_strsplit(line, '-');
	if (names[0][0] == 'L' || names[1][0] == 'L' || arr_size(names) != 2)
		ret = 0;
	if (ft_strequ(names[0], names[1]) == 1)
		ret = 0;
	if (ret != 0)
		ret = make_link(rooms, names[0], names[1]);
	free(names[0]);
	free(names[1]);
	free(names);
	return (ret);
}

t_room	*make_room()
{
	t_room		*room;

	room = (t_room*)malloc(sizeof(t_room));
	room->links = NULL;
	room->name = NULL;
	return (room);
}

int		check_coordinates(t_roomlist *farm, int coord_x, int coord_y)
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

int		clean_room(t_room *room)
{
	if (room->name != NULL)
		free(room->name);
	free(room);
	room = NULL;
	return (0);
}

int		process_room(char *line, t_roomlist *rooms, int room_status, int *room_index)
{
	t_room	*room;
	char	*temp;
	char	*iter;
	int		temp_int;
	int		i;

	room = make_room();
	i = 0;
	if (line[0] == 'L')
//		return (clean_room(room));
		return (0);
	if ((temp = ft_strchr(line, ' ')) == '\0')
		return (0);
//		return (clean_room(room));
	iter = line;
	while (iter != temp)
	{
		iter++;
		i++;
	}
	temp++;
	room->name = ft_strsub(line, 0, i);
	if (ft_isdigit(temp[0]) && (temp_int = ft_atoi(temp)) >= 0)
	{
		room->coord_x = temp_int;
		temp = ft_strchr(temp, ' ');
		if (temp == NULL)
//			return (clean_room(room));
			return (0);
		temp++;
		if ((ft_isdigit(temp[0]) && (temp_int = ft_atoi(temp)) >= 0))
		{
			room->coord_y = temp_int;
			if (ft_strchr(temp, ' ') == '\0')
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
				if (check_coordinates(rooms, room->coord_x, room->coord_y) == 0 || find_roomlist_elem_by_name(rooms, room->name) != NULL)
//					return (clean_room(room));
					return (0);
				add_room(&rooms, room);
				return (1);
			}
		}
	}
	return (0);
}

int		check_valid(char *line, t_roomlist *rooms, int room_status, int *room_index, int *links_started)
{
	if (ft_strchr(line, '-') == '\0')
	{
		if (*links_started == 1)
			return (0);
		return (process_room(line, rooms, room_status, room_index));
	}
	else
	{
		if (*links_started == 0)
			*links_started = 1;
		return (process_link(line, rooms));
	}
}

int		process_line(char **line, t_roomlist *rooms, int *room_status, int *room_index, int *links_started, char **out)
{
	int		status;

	status = 1;

	if ((*line)[0] == '\0')
		return (0);
	if (ft_strequ((*line), "##start") == 1)
	{
		if (*room_status == 1)
			return (0);
		*room_status = -1;
	}
	else if (ft_strequ((*line), "##end") == 1)
	{
		if (*room_status == -1)
			return (0);
		*room_status = 1;
	}
	else if ((*line)[0] == '#' && (*line)[1] == '#' && (*line)[2] != '#')
	{
		free(*line);
		*line = NULL;
		return (status);
	}
	else if ((*line)[0] == '#')
	{
//		*room_status = 0;;
		;
	}
	else
	{
		status = check_valid((*line), rooms, *room_status, room_index, links_started);
		*room_status = 0;
	}
//	if (*line != NULL)
	(*out) = freejoin(*out, *line);
	(*out) = freejoin(*out, ft_strdup("\n"));
//	printf("%s\n", *line);
//	free((*line));
	*line = NULL;
	return (status);
}

t_roomlist		*get_farm(int *ants, char **out)
{
	t_roomlist *rooms;
	char *line;
//	int fd;
	int room_status;
	int room_index;
	int start_end_counter;
	int links_started;

	(*out) = ft_strnew(1);
	links_started = 0;
	start_end_counter = 0;
	room_status = 0;
	room_index = 0;
//	fd = open(name, O_RDONLY);
	rooms = make_list();
	if (get_next_line(0, &line))
	{
		*ants = handle_first_line(line);
		if (*ants <= 0)
			return (NULL);
//		printf("%s\n", line);
//		free(line);
		(*out) = freejoin((*out), line);
		(*out) = freejoin((*out), ft_strdup("\n"));
		line = NULL;
	}
	while (get_next_line(0, &line))
	{
		if (room_status == -1 || room_status == 1)
			start_end_counter++;
		if (process_line(&line, rooms, &room_status, &room_index, &links_started, out) == 0)
		{
			if (ft_strequ(line, "") == 1)
				break;
			free_farm(rooms);
			free(*out);
			return (NULL);
		}
//		ft_strjoin(out, line);
	}
	if (start_end_counter != 2)
	{
		free_farm(rooms);
		return (NULL);
	}
//	printf("%s\n", out);
//	free(out);
	free(line);
	return (rooms);
}