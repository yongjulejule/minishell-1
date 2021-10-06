/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:43:22 by ghan              #+#    #+#             */
/*   Updated: 2021/10/06 12:44:08 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	check_var_overlap(t_exp_arg *av_lst)
{
	t_exp_arg	*cur;
	t_exp_arg	*av_next;
	char		*pos;

	cur = av_lst->next;
	while (cur)
	{
		av_next = cur->next;
		while (av_next)
		{
			pos = ft_strchr(av_next->arg, '=');
			if (!pos
				&& !ft_strncmp(av_next->arg, cur->arg, ft_strlen(av_next->arg)))
				av_next->flag = 0;
			else if (pos
				&& !ft_strncmp(av_next->arg, cur->arg, pos - av_next->arg))
				cur->flag = 0;
			av_next = av_next->next;
		}
		cur = cur->next;
	}
}

void	check_exp_argv(t_exp_arg *av_lst, int *cnt_valid)
{
	t_exp_arg	*cur;
	int			k;

	cur = av_lst->next;
	while (cur)
	{
		k = 0;
		if (cur->flag && cur->arg[k]
			&& (cur->arg[k] == '_' || ft_isalpha(cur->arg[k])))
		{
			k++;
			while (cur->flag && cur->arg[k]
				&& (cur->arg[k] == '_' || ft_isalnum(cur->arg[k])))
				k++;
		}
		if (!k || (cur->arg[k] && cur->arg[k] != '='))
		{
			exp_unset_invalid_arg_msg('e', cur->arg);
			cur->flag = 0;
		}
		else
			(*cnt_valid)++;
		cur = cur->next;
	}
}
