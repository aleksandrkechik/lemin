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

int				process_line(char **line, t_roomlist *rooms,
		t_roominfo *info, char **out)
{
	int		status;

	status = 1;
	if ((line_check(line, info)) == 0)
		return (0);
	else if ((*line)[0] == '#' && (*line)[1] == '#' && (*line)[2] != '#')
	{
		free(*line);
		*line = NULL;
		return (status);
	}
	else if ((*line)[0] == '#')
		;
	else
	{
		status = check_valid((*line), rooms,
			info);
		info->room_status = 0;
	}
	(*out) = freejoin(*out, *line);
	(*out) = freejoin(*out, ft_strdup("\n"));
	*line = NULL;
	return (status);
}

t_roominfo		init_info(void)
{
	t_roominfo		info;

	info.links_started = 0;
	info.start_end_counter = 0;
	info.room_status = 0;
	info.room_index = 0;
	return (info);
}

int				read_rooms(char *line, t_roominfo *info, t_roomlist *rooms,
		char **out)
{
	while (get_next_line(0, &line))
	{
		if (info->room_status == -1 || info->room_status == 1)
			info->start_end_counter++;
		if (process_line(&line, rooms, info, out) == 0)
		{
			if (ft_strequ(line, "") == 1)
				break ;
			free_farm(rooms);
			free(*out);
			return (0);
		}
	}
	return (1);
}

t_roomlist		*get_farm(int *ants, char **out)
{
	t_roomlist		*rooms;
	char			*line;
	t_roominfo		info;

	(*out) = ft_strnew(1);
	info = init_info();
	rooms = make_list();
	if (get_next_line(0, &line))
	{
		*ants = handle_first_line(line);
		if (*ants <= 0)
			return (NULL);
		(*out) = freejoin((*out), line);
		(*out) = freejoin((*out), ft_strdup("\n"));
		line = NULL;
	}
	if ((read_rooms(line, &info, rooms, out)) == 0)
		return (NULL);
	if (info.start_end_counter != 2)
	{
		free_farm(rooms);
		return (NULL);
	}
	free(line);
	return (rooms);
}
