/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bring_balance_to_the_force_not_destroy_it.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:36:26 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/14 14:12:21 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void			balancing_cycle(t_routelist *longest, t_routelist *shortest,
		int *ants_remain, t_routelist *routes)
{
	int balanced;

	balanced = 0;
	while (balanced == 0)
	{
		if ((longest->moves - shortest->moves == 0 ||
			longest->moves - shortest->moves == 1))
			balanced = 1;
		if ((*ants_remain) > 0)
		{
			shortest->moves++;
			shortest->ants++;
			(*ants_remain)--;
		}
		if (longest->ants > 1)
		{
			longest->moves--;
			longest->ants--;
			(*ants_remain)++;
		}
		longest = find_longest(routes);
		shortest = find_shortest(routes);
	}
}

void			bring_balance_to_the_force_not_destroy_it(t_routelist *routes,
			int ants_remain, int ants_to_route)
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
	longest = find_longest(routes);
	shortest = find_shortest(routes);
	balancing_cycle(longest, shortest, &ants_remain, routes);
	while (ants_remain > 0)
	{
		shortest = find_shortest(routes);
		ants_remain--;
		shortest->moves++;
		shortest->ants++;
	}
}
