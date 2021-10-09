/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_arg_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 22:47:33 by ghan              #+#    #+#             */
/*   Updated: 2021/10/09 22:00:06 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exp_lst_size(t_exp_arg *arg)
{
	int	size;

	size = 0;
	while (arg)
	{
		size++;
		arg = arg->next;
	}
	return (size);
}

t_exp_arg	*exp_lst_init(char *arg)
{
	t_exp_arg	*elem;

	elem = (t_exp_arg *)ft_calloc(1, sizeof(t_exp_arg));
	elem->arg = arg;
	elem->flag = IS_VAL;
	elem->next = NULL;
	return (elem);
}

t_exp_arg	*exp_lstlast(t_exp_arg *elem)
{
	if (elem == NULL)
		return (NULL);
	while (elem->next)
		elem = elem->next;
	return (elem);
}

void	exp_lst_addback(t_exp_arg *hd, t_exp_arg *new)
{
	t_exp_arg	*last;

	if (!hd)
		return ;
	last = exp_lstlast(hd);
	last->next = new;
}

void	free_argv_lst(t_exp_arg **av_lst)
{
	t_exp_arg	*elem;

	elem = *av_lst;
	while (elem)
	{
		free(elem->arg);
		elem = elem->next;
		free(*av_lst);
		*av_lst = elem;
	}
	*av_lst = NULL;
}
