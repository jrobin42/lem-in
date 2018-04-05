/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/05 04:32:33 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		lemin;

	ft_bzero(&lemin, sizeof(lemin));
	if (collect_parse_data(&lemin) == FAILURE)
	{
		ft_printf("ERROR : WRONG INPUT\n%s\n", lemin.error_type);
		return (1);
	}
	if (resolve_lemin(&lemin, lemin.adj_mtx) == FAILURE)
	{
		ft_printf("ERROR : NO SOLUTION\n");
		return (1);
	}
	return (0);
}
