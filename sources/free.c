/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 23:42:11 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/29 00:59:54 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del(void *s, size_t n)
{
	if (s)
		ft_strdel((char**)&(((t_room*)s)->name));
	ft_memdel(&s);
	(void)n;
}

void	del_to_print(void *s, size_t n)
{
	ft_strdel((char**)&s);
	(void)n;
}

void	free_rooms(t_room **r, int nb_rooms)
{
	int		i;

	i = 0;
	while (r && i < nb_rooms)
	{
		if (r[i])
			ft_strdel(&(r[i]->name));
		ft_memdel((void**)&(r[i]));
		++i;
	}
	ft_memdel((void**)&r);
}

void	free_mat(int **mat, int max)
{
	int		j;

	j = 0;
	while (j < max)
	{
		ft_memdel((void**)&(mat[j]));
		++j;
	}
	free(mat);
	mat = NULL;
}

void	free_resolve_lemin(int n, int **paths, int *len_paths)
{
	int		i;

	i = 0;
	while (i < n)
	{
		ft_memdel((void**)&(paths[i]));
		++i;
	}
	ft_memdel((void**)&paths);
	ft_memdel((void**)&len_paths);
}
