/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 00:21:02 by ghan              #+#    #+#             */
/*   Updated: 2021/09/27 16:30:30 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

static void	check_unset_argv(t_exp_arg *av_lst, int *cnt_val)
{
	int	i;

	while (av_lst)
	{
		i = -1;
		while (av_lst->arg[++i])
		{
			if (av_lst->arg[i] != '_' && !ft_isalpha(av_lst->arg[i]))
			{
				exp_unset_invalid_arg_msg('u', av_lst->arg);
				av_lst->flag = 0;
				break ;
			}
		}
		if (av_lst->arg[i] == '\0')
			(*cnt_val)++;
		av_lst = av_lst->next;
	}
}

static void	fill_rem_env(t_exp_arg *ev_lst, t_exp_arg *av_lst, char ***envp )
{
	t_exp_arg	*cur_arg;
	t_exp_arg	*cur_ev;
	int			idx;
	int			cnt;

	cnt = 0;
	cur_ev = ev_lst->next;
	while (cur_ev)
	{
		if (cur_ev->flag)
			cnt++;
		cur_ev = cur_ev->next;
	}
	*envp = (char **)ft_calloc(cnt + 1, sizeof(char *));
	idx = 0;
	cur_ev = ev_lst->next;
	while (cur_ev)
	{
		if (cur_ev->flag)
			*(*envp + idx++) = ft_strdup(cur_ev->arg);
		cur_ev = cur_ev->next;
	}
	free_argv_lst(&ev_lst);
}

static void	unset_env_var(char ***envp, t_exp_arg *av_lst)
{
	t_exp_arg	*cur_arg;
	t_exp_arg	*cur_ev;
	t_exp_arg	*ev_lst;
	char		**to_fr;

	ev_lst = argv_to_lst(*envp);
	to_fr = *envp;
	cur_ev = ev_lst->next;
	while (cur_ev)
	{
		cur_arg = av_lst->next;
		while (cur_arg)
		{
			if (!ft_strncmp(cur_arg->arg, cur_ev->arg,
					ft_strlen(cur_arg->arg)))
			{
				cur_ev->flag = 0;
				break ;
			}
			cur_arg = cur_arg->next;
		}
		cur_ev = cur_ev->next;
	}
	fill_rem_env(ev_lst, av_lst, envp);
	free_double_ptr((void ***)&to_fr);
}

int	unset(const char *path, char *const argv[], char ***const envp)
{
	t_exp_arg	*av_lst;
	int			cnt_val;
	int			cnt_rem;

	g_exit_code = EXIT_SUCCESS;
	cnt_val = 0;
	av_lst = NULL;
	if (ft_strsetlen((char **)argv) > 1)
	{
		av_lst = argv_to_lst((char **)argv);
		check_unset_argv(av_lst->next, &cnt_val);
		if (cnt_val)
			unset_env_var(envp, av_lst);
	}
	if (av_lst)
		free_argv_lst(&av_lst);
	return (g_exit_code);
}
