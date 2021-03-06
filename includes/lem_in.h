/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:49:02 by jrobin            #+#    #+#             */
/*   Updated: 2018/05/06 18:04:40 by jrobin           ###   ########.fr       */
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
# define SIZE_ERROR 50

typedef struct		s_room
{
	char			*name;
	int				ant;
	int				coord_x;
	int				coord_y;
}					t_room;

typedef struct		s_path
{
	int				*path;
	struct s_path	*next;
}					t_path;

typedef struct		s_lemin
{
	char			error_type[SIZE_ERROR];
	char			**data;
	int				step;
	int				nb_rooms;
	int				**adj_mtx;
	int				room_type;
	t_list			*to_print;
	t_list			*all;
	t_list			*start;
	t_list			*end;
	t_room			**rooms;
	int				nb_ants;
	int				opt;
	int				arrived_ants;
}					t_lemin;

int					collect_parse_data(t_lemin *lemin, char *line);
int					is_room(char *line, t_lemin *lemin);
int					is_command(char *line, t_lemin *lemin);
int					is_comment(char *line, t_lemin *lemin);
int					is_start_end(char *line, t_lemin *lemin);
int					wrong_nb_params(char **line);
int					arent_coord(char **line);
int					stock_data_room(char **data, t_lemin *lemin);
int					error_room(t_lemin *lemin);
int					get_nb_ants(char **line, t_lemin *lemin);
int					create_adjacency_matrix(t_room ***rooms, t_lemin *lemin,
				char *line);
int					resolve_lemin(t_lemin *lemin, int **mat);
void				init_tab(int **prev, int **gap, int **next_curr, int max);
int					count_paths(int **mat, int max);
void				set_next_curr(int *next_curr, int new, int max);
void				delete_access(int **mat, int *path, int max);
void				print_soluce(int **paths, t_lemin *l, int nb_paths,
				int *len_paths);
void				free_mat(int **mat, int max);
void				print_adj_mtx(int max, int **mat);
void				del(void *s, size_t n);
void				del_to_print(void *s, size_t n);
void				free_rooms(t_room **r, int nb_rooms);
void				free_lemin(t_lemin l);
void				free_mat(int **mat, int max);
void				free_resolve_lemin(int n, int **paths, int *len_paths);
void				usefull_paths(int **ants_for_each, int nb_ants, int *len_p,
				int *nb_paths);
void				pull_ant(t_lemin *l, t_room **r, int *path, int len_p);
void				aff_paths(t_lemin *l, int **path, int *len_paths,
				int nb_paths);

#endif
