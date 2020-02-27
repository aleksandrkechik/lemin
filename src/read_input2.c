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

t_room		*make_room(void)
{
	t_room		*room;

	room = (t_room*)malloc(sizeof(t_room));
	room->links = NULL;
	room->name = NULL;
	return (room);
}

int			check_valid(char *line, t_roomlist *rooms,
						t_roominfo *info)
{
	if (ft_strchr(line, '-') == '\0')
	{
		if (info->links_started == 1)
			return (0);
		return (process_room(line, rooms,
				info->room_status, &info->room_index));
	}
	else
	{
		if (info->links_started == 0)
			info->links_started = 1;
		return (process_link(line, rooms));
	}
}

int			line_check(char **line, t_roominfo *info)
{
	if ((*line)[0] == '\0')
		return (0);
	if (ft_strequ((*line), "##start") == 1)
	{
		if (info->room_status == 1)
			return (0);
		info->room_status = -1;
	}
	else if (ft_strequ((*line), "##end") == 1)
	{
		if (info->room_status == -1)
			return (0);
		info->room_status = 1;
	}
	return (1);
}
