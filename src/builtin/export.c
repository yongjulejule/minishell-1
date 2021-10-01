/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 10:36:58 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/01 15:05:39 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

static void	check_var_overlap(t_exp_arg *av_lst)
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

static void	check_exp_argv(t_exp_arg *av_lst, int *cnt_valid)
{
	t_exp_arg	*cur;
	int			k;

	cur = av_lst->next;
	while (cur)
	{
		k = 0;
		while (cur->flag && cur->arg[k]
			&& (cur->arg[k] == '_' || ft_isalpha(cur->arg[k])))
			k++;
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

static void	skip_or_sub_env(char ***ev, t_exp_arg *avs, char **to_fr, int *idx)
{
	t_exp_arg	*cur;
	char		*pos;

	while (to_fr[++(*idx) + 1])
	{
		cur = avs->next;
		while (cur)
		{
			pos = ft_strchr(cur->arg, '=');
			if (cur->flag && !pos
				&& !ft_strncmp(cur->arg, to_fr[*idx], ft_strlen(cur->arg)))
				cur->flag = 0;
			else if (cur->flag && pos
				&& !ft_strncmp(cur->arg, to_fr[*idx], pos - cur->arg))
				break ;
			cur = cur->next;
		}
		if (cur && cur->flag)
		{
			*(*ev + *idx) = strdup_skip_qm(cur->arg, 0, 0);
			cur->flag = 0;
		}
		else
			*(*ev + *idx) = ft_strdup(to_fr[*idx]);
	}
}

static void	add_env(char ***ev, t_exp_arg *avs, int new_len)
{
	char		**to_fr;
	char		*tmp;
	int			idx;
	t_exp_arg	*cur;

	to_fr = *ev;
	tmp = to_fr[ft_strsetlen(to_fr) - 1];
	*ev = (char **)ft_calloc(new_len + 1, sizeof(char *));
	idx = -1;
	skip_or_sub_env(ev, avs, to_fr, &idx);
	cur = avs->next;
	while (cur)
	{
		if (cur->flag)
			append_env_var(ev, cur->arg, &idx);
		cur = cur->next;
	}
	*(*ev + idx) = strdup_skip_qm(tmp, 0, 0);
	free_double_ptr((void ***)&to_fr);
}

int	exprt(const char *path, char *const argv[], char ***const envp)
{
	t_exp_arg	*av_lst;
	int			cnt_val;
	int			o_len;
	int			i;

	av_lst = NULL;
	cnt_val = 0;
	g_exit_code = EXIT_SUCCESS;
	o_len = ft_strsetlen((char **)(*envp));
	if (!argv[1])
		exprt_no_arg((char **)(*envp), o_len);
	else
	{
		av_lst = argv_to_lst((char **)argv);
		check_exp_argv(av_lst, &cnt_val);
		check_var_overlap(av_lst);
		if (cnt_val)
			add_env((char ***)envp, av_lst, o_len + cnt_val);
	}
	if (av_lst)
		free_argv_lst(&av_lst);
	return (g_exit_code);
}
