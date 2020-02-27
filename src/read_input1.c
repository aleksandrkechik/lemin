/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:38:09 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/15 14:01:19 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

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

	if ((first_room = find_room_by_name(rooms, room_1)) == NULL
		|| (second_room = find_room_by_name(rooms, room_2)) == NULL ||
		find_room_by_name(first_room->links, room_2) != NULL
		|| find_room_by_name(second_room->links, room_1) != NULL)
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

int		count_dashes(char *line)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (line[i])
	{
		if (line[i] == '-')
			ret++;
		i++;
	}
	if (ret == 1)
		return (1);
	return (0);
}

int		process_link(char *line, t_roomlist *rooms)
{
	char	**names;
	int		ret;

	ret = -1;
	if (count_dashes(line) == 0)
		ret = 0;
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
