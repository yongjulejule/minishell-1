/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 00:21:02 by ghan              #+#    #+#             */
/*   Updated: 2021/09/27 03:41:57 by ghan             ###   ########.fr       */
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

static void	fill_remaining_envp(char **envp, t_exp_arg *av_lst, char **to_fr)
{
	t_exp_arg	*cur;
	int			idx;
	int			k;

	k = 0;
	idx = 0;
	while (to_fr[k])
	{
		cur = av_lst->next;
		while (cur)
		{
			if (cur->flag
				&& !ft_strncmp(cur->arg, to_fr[k], ft_strlen(cur->arg)))
			{
				k++;
				cur->flag = 0;
				break ;
			}
			cur = cur->next;
		}
		if (to_fr[k])
		{
			envp[idx++] = ft_strdup(to_fr[k]);
			k++;
		}
	}
}

static void	unset_env_var(char ***envp, t_exp_arg *av_lst)
{
	t_exp_arg	*cur;
	char		**to_fr;
	int			cnt;
	int			i;

	cnt = 0;
	i = -1;
	to_fr = *envp;
	while (to_fr[++i])
	{
		cur = av_lst->next;
		while (cur)
		{
			if (!ft_strncmp(cur->arg, to_fr[i],
				ft_strlen(cur->arg)))
			{
				cnt++;
				break ;
			}
			cur = cur->next;
		}
	}
	*envp = (char **)ft_calloc(ft_strsetlen(*envp) + 1,
		sizeof(char *));
	fill_remaining_envp(*envp, av_lst, to_fr);
	free_double_ptr((void ***)&to_fr);
}

int	unset(const char *path, char *const argv[], char ***const envp)
{
	t_exp_arg	*av_lst;
	int			cnt_val;

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
