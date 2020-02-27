/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 12:30:27 by hturkatr          #+#    #+#             */
/*   Updated: 2020/02/14 16:53:54 by hturkatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_FIRST_LEMIN_H
#define LEMIN_FIRST_LEMIN_H

#include <stdio.h>

# include "../printflib/ft_printf.h"
# include <fcntl.h>

# define BUFF_SIZE 2048
# define BLOCKED -1000

typedef struct				s_room t_room;
typedef struct				s_roomlist t_roomlist;
typedef struct				s_route t_route;
typedef struct				s_routelist t_routelist;
typedef struct				s_roominfo t_roominfo;
typedef struct				s_ant t_ant;


int				get_next_line(const int fd, char **line);

t_roomlist		*get_farm(int *ants, char **out);

typedef struct			s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
	int				start;
	int				end;
	int				index;
	int				dist_to_start;
	int				dist_to_end;
	int				is_route_part;
	t_roomlist		*links;
	t_roomlist		*link_from_in_to_out;
	t_roomlist		*links_backup;
	int				parent;
}						t_room;

t_room			*find_room(t_roomlist *rooms, int index);
t_room			*find_room_by_name(t_roomlist *rooms, char *name);

typedef struct			s_roomlist
{
	t_roomlist		*next;
	t_room			*room;
	t_roomlist		*prev_in_route;
	int				cost_to;
	int				cost_from;
	int				length;
}						t_roomlist;

t_roomlist		*make_list();
void			add_room(t_roomlist **head, t_room *room);
void			print_room_sequence(t_roomlist *list);
void			print_room_links(t_roomlist *list);
int				get_length(t_roomlist *list);
void			print_farm(t_roomlist *list);
void			print_dist_to_end(t_roomlist *list);
t_roomlist		*get_start(t_roomlist *list);
t_roomlist		*get_end(t_roomlist *list);
void			get_distances(t_roomlist *rooms);
int				contain_room(t_roomlist *list, t_roomlist *room);
void			add_to_queue(t_roomlist *queue, t_roomlist *elem);
t_roomlist		*take_from_queue(t_roomlist **queue);
t_roomlist		*get_shortest_route(t_roomlist *farm);
t_roomlist		*get_shortest_route2(t_roomlist *farm, t_roomlist *room);
t_roomlist		*find_roomlist_elem(t_roomlist *rooms, int index);
void			modify_link_cost(t_roomlist *from, t_roomlist *to, int new_cost);
void			exclude_route(t_roomlist *farm, t_roomlist *route);
int				get_cost(t_roomlist *from, t_roomlist *to);
void			clean_distances(t_roomlist *rooms);
void			modify_graph(t_roomlist *farm);
int				get_cost_from(t_roomlist *from, t_roomlist *to);
t_roomlist		*find_roomlist_elem_by_name(t_roomlist *rooms, char *name);
void			print_dist_to_start(t_roomlist *list);
void			add_room_to_head(t_roomlist **head, t_room *room);
void			have_intersection(t_roomlist *shortest_1, t_roomlist *shortest_2);
int				get_route_length(t_roomlist *route);
void			reinclude_route(t_roomlist *farm, t_roomlist *route);
int				get_number_of_routes(t_routelist *routes);
int				check_room_uniqueness(t_routelist *routes);
int				process_link(char *line, t_roomlist *rooms);
int				handle_first_line(char *line);
int				check_valid(char *line, t_roomlist *rooms,
					   t_roominfo *info);
int				line_check(char **line, t_roominfo *info);

typedef struct				s_routelist
{
	t_roomlist		*route;
	t_routelist		*next;
	int				length;
	int				moves;
	int				ants;
	t_ant			*first;
	t_ant			*last;
	int				last_route;
	int				ants_moving;
}							t_routelist;

t_routelist		*make_routelist();
void			add_route(t_routelist *list, t_roomlist *route);
int				count_moves(t_routelist *routes, int ants);
void			print_routes_info(t_routelist *routes);
void			process_routes(t_roomlist *farm, int ants, char *out);
t_roomlist		*farm_creation(int *ants, char **out);
void	include_routes(t_roomlist *farm, t_routelist *routes);
void	exclude_routes(t_roomlist *farm, t_routelist *routes);
t_routelist			*make_backup(t_routelist *routes);
t_roomlist			*get_one_more(t_roomlist *farm,
									t_routelist **routes, t_routelist *backup);
int					compare_moves(t_routelist **routes,
									 int ants, int moves, t_routelist *backup);
int		process_room(char *line, t_roomlist *rooms,
						int room_status, int *room_index);
t_room		*make_room(void);

//input2 stuff
void		handle_links(t_roomlist *farm);
int			is_in_shortest_tree(t_roomlist *from, t_roomlist *to);


//ants movements

typedef struct				s_ant
{
	int				number;
	int				at_end;
	t_roomlist		*location;
	t_ant			*next;
	t_ant			*prev;
}							t_ant;

int				move_ant(t_ant *ant, t_routelist *route);
void			move_ant_through_route(t_ant ant);
//void	give_birth_to_the_ant(int number, t_routelist **route);
void			process_ant_migration(t_routelist *routes);
t_routelist		*copy_routelist(t_routelist *list);
int				get_startroom_links(t_roomlist *farm);
void			check_intersections(t_routelist *routes);
int				get_room_links(t_roomlist *farm, char *name);
t_roomlist		*reverse_list(t_roomlist *list);
void			make_links_from_in_to_out(t_roomlist *route);
void			clean_links_from_in_to_out(t_roomlist *route);
void			clean_links_routes(t_routelist *routes);
void			make_links_routes(t_routelist *routes);
void			make_backup_links(t_roomlist *farm);
void			pop_link(t_roomlist *from, t_roomlist *to);
void			give_birth_to_the_ant(int number, t_routelist *route);
void			move_all_ants(t_routelist *route);
void			width_search2(t_roomlist *rooms, t_roomlist *root,
					  t_roomlist **checked, t_roomlist *order);

////freeing_stuff
void	free_roomlist(t_roomlist *list);
void	free_routelist(t_routelist *list);
void	free_farm(t_roomlist *farm);
void	free_ants(t_routelist *route);
void	free_route_copy(t_routelist *list);
int		check_name(char *name);
t_roomlist		*get_shortest_route_from_room(t_roomlist *farm, char *name);
void		add_new_cost_to(t_roomlist **room, int cost);
t_routelist		*find_longest(t_routelist *routes);
t_routelist		*find_shortest(t_routelist *routes);
void			bring_balance_to_the_force_not_destroy_it(t_routelist *routes,
		int ants_remain, int ants_to_route);
void			get_routes_info(t_routelist *routes,
								int *longest, int *shortest);
void	handle_intersection(t_roomlist *shortest_1, t_roomlist *shortest_2,
							int intersection_1, int intersection_2);

typedef struct	s_roominfo
{
	int				room_status;
	int				room_index;
	int				start_end_counter;
	int				links_started;
}				t_roominfo;
#endif //LEMIN_FIRST_LEMIN_H
