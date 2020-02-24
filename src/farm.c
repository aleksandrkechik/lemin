/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:16:39 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/15 13:56:10 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

t_routelist			*make_backup(t_routelist *routes)
{
	t_routelist *backup;

	backup = copy_routelist(routes);
	return (backup);
}

int					get_room_links(t_roomlist *farm, char *name)
{
	t_roomlist *iter;
	int i;

	i = 0;
	iter = farm->next;
	while (iter != NULL)
	{
		if (ft_strequ(name, iter->room->name) == 1)
		{
			iter = iter->room->links->next;
			while (iter != NULL)
			{
				i++;
				iter = iter->next;
			}
			return (i);
		}
		iter = iter->next;
	}
	return (0);
}

void				process_routes(t_roomlist *farm, int ants, char *out)
{
	t_roomlist		*shortest;
	t_routelist		*routes;
	t_routelist		*backup;
	int				moves;
	int				new_moves;
	int				max;

	routes = make_routelist();
	if ((shortest = get_shortest_route(farm)) == NULL)
	{
		free_routelist(routes);
		free_farm(farm);
		printf("ERROR\n");
		return ;
	}
	make_links_from_in_to_out(shortest);
	add_route(routes, shortest);
	moves = count_moves(routes, ants);
	max = get_startroom_links(farm);
	while (max)
	{
		backup = make_backup(routes);
		exclude_route(farm, shortest);
		modify_graph(farm);
		clean_distances(farm);
		get_distances(farm);
		if ((shortest = get_shortest_route(farm)) == NULL)
		{
			free_routelist(routes);
			routes = backup;
			break;
		}
		clean_links_routes(routes);
		add_route(routes, shortest);
		check_intersections(routes);
		make_links_routes(routes);
		new_moves = count_moves(routes, ants);
		if (new_moves > moves)
		{
			free_routelist(routes);
			routes = backup;
			break;
		}
		moves = new_moves;
		max--;
		free_routelist(backup);
	}
	count_moves(routes, ants);
	printf("%s\n", out);
	free(out);
	process_ant_migration(routes);
	free_routelist(routes);
	free_farm(farm);
}

t_roomlist			*farm_creation(int *ants, char **out)
{
	t_roomlist		*farm;

	if ((farm = get_farm(ants, out)) == NULL)
	{
		return (NULL);
	}
	get_distances(farm);
	return (farm);
}