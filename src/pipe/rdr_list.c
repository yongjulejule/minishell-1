/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 08:56:05 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/16 09:03:14 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

t_rdr	*rdr_lst_newone(int rdr_flag, char *limiter, char *file)
{
	t_rdr	*rdr_node;

	rdr_node = (t_rdr *)ft_calloc(1, sizeof(t_rdr));
	rdr_node->limiter = limiter;
	rdr_node->file = file;
	rdr_node->rdr_flag = rdr_flag;
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
