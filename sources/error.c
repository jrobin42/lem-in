/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 20:21:14 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/10 20:45:54 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		same_coord(t_list *data)
{
	t_list	*move;

	move = data->next;
	while (move)
	{
		if (((t_room*)data->content)->coord_x == ((t_room*)move->content)->coord_x && ((t_room*)data->content)->coord_y == ((t_room*)move->content)->coord_y)
			return (TRUE);
		move = move->next;
	}
		ft_printf("%s\n", ((t_room*)data->next->content)->name);
	return (data && data->next ? TRUE : FALSE);
}

int		error_room(t_lemin *lemin)
{
	int			i;
	t_list		*tmp;

	i = 0;
	tmp = lemin->all;
	while (tmp)
	{
		if (same_coord(tmp))
		{
			ft_printf("error rooooom\n");
			return (FAILURE);
		}
		tmp = tmp->next;
	}
	ft_printf("no error room\n");
	return (SUCCESS);
}
