/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 21:40:00 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/26 20:44:38 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		delete_biggest_room(t_list *prev, t_list **path, int i, int max)
{
	ft_printf("delete path\n");
	while (i < max)
	{
		ft_printf("m[i] = [%d]\n", ((t_path*)(*path)->content)->path[i]);
		++i;
	}
	prev->next = (*path)->next;
	free(((t_path*)(*path)->content)->path);
	free((t_path*)(*path)->content);
	free(*path);
}

/*Necessaire de reset used_room !*/
static int		same_rooms(t_list *path, int max, t_lemin *lemin)
{
	int		j;

	j = 1;
	while (j < max && PATH->path[j] != -1)
	{
		if (lemin->used_rooms[PATH->path[j]] == 1)
			return (TRUE);
		lemin->used_rooms[PATH->path[j]] = 1;
		++j;
	}
	return (FALSE);
}

static void		compare_paths(t_list **path, int nb_ants, t_lemin *lemin)
{
	t_list		*begin;
	t_list		*prev;
	int			total_len;

	begin = *path;
	prev = *path;
	*path = (*path)->next;
	total_len = ((t_path*)begin->content)->len_path;
	same_rooms(begin, lemin->nb_rooms, lemin);
	while (total_len < nb_ants && *path)
	{
		if (same_rooms(*path, lemin->nb_rooms, lemin))
		{
			delete_biggest_room(prev, path, 0, lemin->nb_rooms);
			*path = prev;
		}
		else
			prev = *path;
		total_len += ((t_path*)begin->content)->len_path;
		*path = (*path)->next;
	}
	if (*path) /*freeeeeeeeee next et tout le reste d'apres*/
		(*path)->next = NULL;
	*path = begin;
}
/*
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
*/
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
/*
static void		dispatch_ants(int nb_ants, t_list *path, int time, t_lemin *lemin)
{
	int		i;
	int		div;
	int		mod;
	t_list	*begin;

	i = 0;
	begin = path;
	div = nb_ants / time;
	mod = nb_ants % time;
	ft_printf("div = %d mod = %d\n", div, mod);
	while (path && div)
	{
		lemin->ants_for_each_path[i] = (PATH->len_path + 1 > div ?
				PATH->len_path + 1 : div);
		div = div - lemin->ants_for_each_path[i];
		path = path->next;
		++i;
	}
	path = begin;
	i = 0;
	while (mod > 0)
	{
		lemin->ants_for_each_path[i] += PATH->len_path > mod ?
			mod : PATH->len_path;
		path = path->next;
		++i;
	}
	path = begin;
	i = 0;
	while (path)
	{
		ft_printf("ANTS FOR EACH %d = %d\n", i, lemin->ants_for_each_path[i]);
		path=path->next;
		++i;
	}
}

static int		count_paths(t_list *path)
{
	int		count;

	count = 0;
	while (path)
	{
		++count;
		path = path->next;
	}
	return (count);
}

static void		walking_ants(int nb_ants, t_list *path, t_lemin *lemin)
{
	t_list		*begin;
	int			time;
	int			tmp;

	begin = path;
	tmp = nb_ants;
	time = 0;
	while (nb_ants > 0)
	{
		nb_ants = nb_ants - PATH->len_path;
		path = path->next;
		if (!path)
		{
			++time;
			path = begin;
		}
	}
	path = begin;
	lemin->ants_for_each_path = ft_memalloc(count_paths(path) * sizeof(int));
	dispatch_ants(tmp, path, time, lemin);
}*/

int				multi_path(t_ants *ants, int nb_ants, t_lemin *lemin, t_list **path)
{
	ft_bzero(lemin->used_rooms, lemin->nb_rooms);
	if (only_one_path(*path) || first_path_is_sufficient(*path, nb_ants))
	{
		ft_printf("ONE PATH\n");
		(*path)->next = NULL;
	}
	else
	{
		ft_printf("MULTI\n");
		compare_paths(path, nb_ants, lemin);
	//	walking_ants(nb_ants, *path, lemin);
	}
//	(void)ants;
	print_solution(ants, *path, lemin);
	return (SUCCESS);
}
