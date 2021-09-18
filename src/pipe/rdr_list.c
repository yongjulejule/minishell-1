/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 08:56:05 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/18 19:51:41 by jun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

t_rdr	*rdr_lst_newone(t_info info, char *limiter, char *file[2])
{
	t_rdr	*rdr_node;

	rdr_node = (t_rdr *)ft_calloc(1, sizeof(t_rdr));
	rdr_node->limiter = limiter;
	rdr_node->file[0] = file[0];
	rdr_node->file[1] = file[1];
	rdr_node->info = info;
	return (rdr_node);
}

void	rdr_lst_add_back(t_rdr **rdr, t_rdr *newnode)
{
	t_rdr	*start;
	t_rdr	*tmp;

	start = *rdr;
	if (!start)
	{
		*rdr = newnode;
		return ;
	}
	tmp = start;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = newnode;
	*rdr = start;
}
