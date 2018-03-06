/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:44:54 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/06 16:45:02 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		is_command(char *s)
{
	if (*s == '#' && *(s + 1) && *(s + 1) == '#')
		return (TRUE);
	return (FALSE);
}

int		is_comment(char *s)
{
	if (*s == '#' && (!*(s + 1) || *(s + 1) != '#'))
		return (TRUE);
	return (FALSE);
}

int		is_valid(char *s)
{
	if (is_comment(s))
		return (SUCCESS);
	if (is_command(s) || wich_command(s, room))
		return (SUCCESS);
}


