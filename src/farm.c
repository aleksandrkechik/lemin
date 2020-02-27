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

t_roomlist			*get_one_more(t_roomlist *farm,
		t_routelist **routes, t_routelist *backup)
{
	t_roomlist *shortest;

	if ((shortest = get_shortest_route(farm)) == NULL)
	{
		free_routelist(*routes);
		(*routes) = backup;
		return (NULL);
	}
	return (shortest);
}

int					compare_moves(t_routelist **routes,
		int ants, int moves, t_routelist *backup)
{
	int		new_moves;

	new_moves = count_moves(*routes, ants);
	if (new_moves > moves)
	{
		free_routelist(*routes);
		(*routes) = backup;
		return (-1);
	}
	return (new_moves);
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
