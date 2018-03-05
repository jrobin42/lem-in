/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:49:02 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/05 21:37:07 by jrobin           ###   ########.fr       */
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

typedef struct	s_lemin
{
	int			tg;
}				t_lemin;

typedef struct	s_ants
{
	int			nb_ants;
	char		**ants;
}				t_ants;

typedef struct	s_rooms
{
	char		**rooms;
}				t_rooms;

int				collect_parse_data(t_lemin *lemin, t_rooms *room, t_ants *ant);

#endif
