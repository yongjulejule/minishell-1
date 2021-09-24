/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 22:47:33 by ghan              #+#    #+#             */
/*   Updated: 2021/09/24 10:49:37 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	ps_lst_size(t_cmds *cmd)
{
	int	size;

	size = 0;
	while (cmd)
	{
		size++;
		cmd = cmd->next;
	}
	return (size);
}

t_cmds	*ps_lst_init(char *cmd)
{
	t_cmds	*elem;

	elem = (t_cmds *)ft_calloc(1, sizeof(t_cmds));
	elem->cmd = cmd;
	elem->next = NULL;
	return (elem);
}

t_cmds	*ps_lstlast(t_cmds *elem)
{
	if (elem == NULL)
		return (NULL);
	while (elem->next)
		elem = elem->next;
	return (elem);
}

void	ps_lst_addback(t_cmds *hd, t_cmds *new)
{
	t_cmds	*last;

	if (!hd)
		return ;
	last = ps_lstlast(hd);
	last->next = new;
}
