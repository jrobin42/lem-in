/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:49:02 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/11 20:16:01 by jrobin           ###   ########.fr       */
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
# define L_ROOM ((t_room*)lemin->all->content)

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
	int				step;
	int				**tubes;
	int				plop; //0->rien 1->start 2->end
	t_list			*to_print;
	t_list			*all;
	t_list			*start;
	t_list			*end;
}					t_lemin;

int					collect_parse_data(t_lemin *lemin, 
										t_ants *ant);
int					is_room(char *line, t_lemin *lemin);
int					is_command(char *line, t_lemin *lemin);
int					is_comment(char *line, t_lemin *lemin);
int					is_start_end(char *line, t_lemin *lemin);
int					stock_data_room(char **data, t_lemin *lemin);
int	is_tube(char *line, t_lemin *lemin);
int					error_room(t_lemin *lemin);

#endif
