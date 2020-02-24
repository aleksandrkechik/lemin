/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 13:51:14 by hturkatr          #+#    #+#             */
/*   Updated: 2020/01/18 13:57:38 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lemin.h"

void		handle_links(t_roomlist *farm)
{
	t_roomlist *a;
	t_roomlist *b;
	t_roomlist *c;
	t_roomlist *d;
	t_roomlist *e;
	t_roomlist *f;

	a = find_roomlist_elem_by_name(farm, "A");
	b = find_roomlist_elem_by_name(farm, "B");
	c = find_roomlist_elem_by_name(farm, "C");
	d = find_roomlist_elem_by_name(farm, "D");
	e = find_roomlist_elem_by_name(farm, "E");
	f = find_roomlist_elem_by_name(farm, "F");

	modify_link_cost(a, c, 2);
	modify_link_cost(c, a, 2);
	modify_link_cost(c, d, 2);
	modify_link_cost(d, c, 2);
	modify_link_cost(b, e, 2);
	modify_link_cost(e, b, 2);
	modify_link_cost(f, e, 2);
	modify_link_cost(e, f, 2);

	printf("\n%d\n", get_cost(find_roomlist_elem_by_name(farm, "A"), find_roomlist_elem_by_name(farm, "C")));
}
