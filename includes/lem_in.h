/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:49:02 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/09 08:30:44 by jrobin           ###   ########.fr       */
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
# define IS_LINK 2
# define END_PARSE -2

# define STEP lemin->step
# define LINE lemin->line
# define L_DATA lemin->data
# define L_ROOM lemin->all->content

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
}					t_room;

typedef struct		s_lemin
{
	char			*line;
	char			**data;
	char			*all_data;
	int				step;
	int				**tubes;
	char			*to_print;
	t_list			*all;
	t_room			*start;
	t_room			*end;
}					t_lemin;

int					collect_parse_data(t_lemin *lemin, t_room *room, 
										t_ants *ant);
int					is_room(t_lemin *lemin);
int					is_command(char *line, t_lemin *lemin);
int					is_comment(char *line, t_lemin *lemin);
int					is_start_end(char *line, t_lemin *lemin);

#endif
