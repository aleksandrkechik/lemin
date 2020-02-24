/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 13:21:52 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/13 13:35:31 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

int main(void)
{
	t_roomlist		*farm;
	int				ants;
	char			*out;

//	if (argc == 2 && check_name(argv[1]))
//	{
//		name = argv[1];
//		if ((farm = farm_creation(&ants, name)) == NULL)
//		{
//			printf ("ERROR\n");
//			return (0);
//		}
//		process_routes(farm, ants);
//	}
//	else
//		printf("ERROR\n");
	if ((farm = farm_creation(&ants, &out)) == NULL)
		{
			printf ("ERROR\n");
			return (0);
		}
	process_routes(farm, ants, out);
	return (0);
}