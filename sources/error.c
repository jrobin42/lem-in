/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 20:21:14 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/11 19:24:17 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		same_coord_or_name(t_list *data)
{
	t_list	*move;

	move = data->next;
	while (move)
	{
		if (((t_room*)data->content)->coord_x == ((t_room*)move->content)->coord_x
		&& ((t_room*)data->content)->coord_y == ((t_room*)move->content)->coord_y)
			return (TRUE);
		if (ft_strequ(((t_room*)data->content)->name, ((t_room*)move->content)->name))
			return (TRUE);
		move = move->next;
	}
	return (FALSE);
}

int		error_room(t_lemin *lemin)
{
	int			i;
	t_list		*tmp;

	i = 0;
	tmp = lemin->all;
	while (tmp)
	{
		if (same_coord_or_name(tmp))
		{
			ft_printf("error rooooom\n");
			return (FAILURE);
		}
		tmp = tmp->next;
	}
	ft_printf("no error room\n");
	return (SUCCESS);
}
