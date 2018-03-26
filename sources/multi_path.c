/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 21:40:00 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/26 01:44:04 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
static void		delete_biggest_room(t_list *prev, t_list **path)
{
	prev->next = (*path)->next;
	free(((t_path*)(*path)->content)->path);
	free((t_path*)(*path)->content);
	free(*path);
}
*/

/*Necessaire de reset used_room !*/
static int		same_rooms(t_list *path, int max, t_lemin *lemin)
{
	int		j;

	j = 0;
	while (j < max && PATH->path[j] != -1)
	{
		if (lemin->used_rooms[PATH->path[j]] == 1)
			return (TRUE);
		lemin->used_rooms[PATH->path[j]] = 1;
		++j;
	}
	return (FALSE);
}

static void		compare_paths(int nb_paths, t_list **path, int max, t_lemin *lemin)
{
	t_list		*begin;
	t_list		*prev;

	begin = *path;
	prev = *path;
	*path = (*path)->next;
	same_rooms(begin, lemin->nb_rooms, lemin);
	while (nb_paths && *path)
	{
		if (same_rooms(*path, max, lemin))
		{
		//	delete_biggest_room(prev, path);
			*path = prev;
		}
		else
			prev = *path;
		*path = (*path)->next;
		--nb_paths;
	}
	if (*path) /*freeeeeeeeee next et tout le reste d'apres*/
		(*path)->next = NULL;
	*path = begin;
}

static int		choose_usefull_paths(int nb_ants, t_list *path)
{
	int		nb_paths;

	nb_paths = 0;
	while (nb_ants > 0 && path)
	{
		nb_ants = nb_ants - PATH->len_path;
		++nb_paths;
		path = path->next;
	}
	return (nb_paths);
}

static int		only_one_path(t_list *path)
{
	if (path->next == NULL)
		return (TRUE);
	return (FALSE);
}

static int		first_path_is_sufficient(t_list *path, int nb_ants)
{
	if (PATH->len_path >= nb_ants
			|| nb_ants <= ((t_path*)path->next->content)->len_path)
		return (TRUE);
	return (FALSE);
}

int				multi_path(int nb_ants, t_lemin *lemin, t_list **path)
{
	int		nb_paths;

	if (only_one_path(*path) || first_path_is_sufficient(*path, nb_ants))
	{
		ft_printf("ONE PATH\n");
		(*path)->next = NULL;
	}
	else
	{
		ft_printf("MULTI\n");
		ft_printf("*path = %p\n", *path);
		nb_paths = choose_usefull_paths(nb_ants, *path);
		ft_printf("*path = %p\n", *path);
		compare_paths(nb_paths, path, lemin->nb_rooms, lemin);
		ft_printf("*path = %p\n", *path);
	}
	print_solution(*path, lemin);
	return (SUCCESS);
}
