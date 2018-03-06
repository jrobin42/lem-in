/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:49:02 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/06 18:25:37 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft_type.h"
# include "libft_str.h"
# include "libft_int.h"
# include "ft_printf.h"

# define SUCCESS 0
# define FAILURE -1
# define TRUE 1
# define FALSE 0

typedef struct		s_lemin
{
	int				**tubes;
}					t_lemin;

typedef struct		s_ants
{
	int				nb_ants;
	char			**ants;
}					t_ants;

typedef struct		s_room
{
	char			*name;
	char			*coord_x;
	char			*coord_y;

}					t_room;

typedef struct		s_all_rooms
{
	struct s_room			room;
	struct s_all_rooms		*next;
}					t_all_rooms;

int					collect_parse_data(t_lemin *lemin, t_room *room, 
										t_ants *ant);
int					get_rooms(void);

#endif
