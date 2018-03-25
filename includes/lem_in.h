/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:49:02 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/25 20:53:02 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft_type.h"
# include "libft_str.h"
# include "libft_int.h"
# include "libft_lst.h"
# include "ft_printf.h"

# define SUCCESS 0
# define FAILURE -1
# define TRUE 1
# define FALSE 0

# define STEP lemin->step
# define LINE lemin->line
# define L_DATA lemin->data
# define L_ROOM ((t_room*)lemin->all->content)
# define START ((t_room*)lemin->start)
# define END ((t_room*)lemin->end)
# define ADJ_MTX lemin->adj_mtx

typedef struct		s_ants
{
	int				nb_ants;
	char			**ants;
}					t_ants;

typedef struct		s_room
{
	char			*name;
	int				coord_x;
	int				coord_y;
//	int				prev;
}					t_room;

typedef struct		s_path
{
	int				*path;
	int				len_path;
}					t_path;

typedef struct		s_lemin
{
//	t_path			**paths;
	char			*line;
	char			**data;
	int				step;
	int				nb_rooms;
	int				**adj_mtx;
	int				*used_rooms;
	int				plop; //0->rien 1->start 2->end
	t_list			*to_print;
	t_list			*all;
	t_list			*start;
	t_list			*end;
	t_room			**rooms;
}					t_lemin;

int					collect_parse_data(t_lemin *lemin, 
										t_ants *ant);
int					is_room(char *line, t_lemin *lemin);
int					is_command(char *line, t_lemin *lemin);
int					is_comment(char *line, t_lemin *lemin);
int					is_start_end(char *line, t_lemin *lemin);
int					stock_data_room(char **data, t_lemin *lemin);
int					error_room(t_lemin *lemin);
int					parse_ants(t_ants *ant, t_lemin *lemin);
int					create_adjacency_matrix(t_room ***rooms, t_lemin *lemin);
int					pathfinding(t_list *path, t_lemin *lemin, int **mat, int *max_nb_paths);
int					print_solution(t_list *path, t_lemin *lemin, int max_nb_paths);

#endif
