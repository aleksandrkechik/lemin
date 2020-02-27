/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:16:39 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/15 13:56:10 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void				apply_routes(t_routelist *routes,
				int ants, char *out, t_roomlist *farm)
{
	count_moves(routes, ants);
	printf("%s\n", out);
	free(out);
	process_ant_migration(routes);
	free_routelist(routes);
	free_farm(farm);
}

int					get_first_route(t_routelist **routes,
				t_roomlist *farm, t_roomlist **shortest)
{
	*routes = make_routelist();
	if (((*shortest) = get_shortest_route(farm)) == NULL)
	{
		free_routelist(*routes);
		free_farm(farm);
		printf("ERROR\n");
		return (0);
	}
	make_links_from_in_to_out(*shortest);
	add_route(*routes, *shortest);
	return (1);
}

void				combine_routes(t_routelist *routes,
					t_roomlist *shortest)
{
	clean_links_routes(routes);
	add_route(routes, shortest);
	check_intersections(routes);
	make_links_routes(routes);
}

void				prepare_for_new_root(t_roomlist *farm)
{
	modify_graph(farm);
	clean_distances(farm);
	get_distances(farm);
}

void				process_routes(t_roomlist *farm, int ants, char *out)
{
	t_roomlist		*shortest;
	t_routelist		*routes;
	t_routelist		*backup;
	int				moves;
	int				max;

	if (!get_first_route(&routes, farm, &shortest))
		return ;
	moves = count_moves(routes, ants);
	max = get_startroom_links(farm);
	while (max)
	{
		backup = make_backup(routes);
		exclude_route(farm, shortest);
		prepare_for_new_root(farm);
		if ((shortest = get_one_more(farm, &routes, backup)) == NULL)
			break ;
		combine_routes(routes, shortest);
		if ((moves = compare_moves(&routes, ants, moves, backup)) == -1)
			break ;
		free_routelist(backup);
		max--;
	}
	apply_routes(routes, ants, out, farm);
}
