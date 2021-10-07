/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:43:22 by ghan              #+#    #+#             */
/*   Updated: 2021/10/07 22:41:43 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	check_argv_flag_cond(t_exp_arg *cur, t_exp_arg *av_n,
				int c_flag, char *pos)
{
	char	*to_fr;

	if (c_flag && !ft_strncmp(av_n->arg, cur->arg, pos - av_n->arg))
	{
		to_fr = av_n->arg;
		if (ft_strchr(cur->arg, '='))
		{
			av_n->arg = ft_strjoin(cur->arg,
					ft_strchr(av_n->arg, '=') + 1);
			free(to_fr);
		}
		cur->flag = 0;
		av_n->flag = 1;
	}
	else if (!pos && !ft_strncmp(av_n->arg, cur->arg, ft_strlen(av_n->arg)))
		av_n->flag = 0;
	else if (pos && !ft_strncmp(av_n->arg, cur->arg, pos - av_n->arg))
		cur->flag = 0;
}

void	check_var_overlap(t_exp_arg *av_lst)
{
	t_exp_arg	*cur;
	t_exp_arg	*av_n;
	char		*pos;
	int			c_flag;

	cur = av_lst->next;
	while (cur->next)
	{
		av_n = cur->next;
		while (av_n)
		{
			c_flag = 0;
			pos = ft_strnstr(av_n->arg, "+=", ft_strlen(av_n->arg));
			if (!pos)
				pos = ft_strchr(av_n->arg, '=');
			else
				c_flag = 1;
			if (cur->flag && av_n->flag)
				check_argv_flag_cond(cur, av_n, c_flag, pos);
			av_n = av_n->next;
		}
		cur = cur->next;
	}
}

static void	check_valid_or_not(int k, t_exp_arg *cur, int *cnt_valid)
{
	if (!k || (cur->arg[k] && cur->arg[k] != '='
			&& ft_strncmp("+=", cur->arg + k, 2)))
	{
		exp_unset_invalid_arg_msg('e', cur->arg);
		cur->flag = 0;
	}
	else
	{
		if (cur->arg[k] && !ft_strncmp("+=", cur->arg + k, 2))
			cur->flag = 2;
		(*cnt_valid)++;
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
		check_valid_or_not(k, cur, cnt_valid);
		cur = cur->next;
	}
}
