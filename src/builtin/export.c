/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 10:36:58 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/27 03:31:04 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

static void	exprt_no_arg(char **envp, int len)
{
	char	**in_order;
	char	*pos;
	int		i;

	in_order = dup_envp(envp, len);
	bubble_sort_strset(in_order, len);
	i = -1;
	while (in_order[++i])
	{
		pos = ft_strchr(in_order[i], '=');
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (pos)
		{
			write(STDOUT_FILENO, in_order[i], pos - in_order[i] + 1);
			ft_putchar_fd('"', STDOUT_FILENO);
			ft_putstr_fd(pos + 1, STDOUT_FILENO);
			ft_putendl_fd("\"", STDOUT_FILENO);
		}
		else
			ft_putendl_fd(in_order[i], STDOUT_FILENO);
	}
	free_double_ptr((void ***)(&in_order));
}

static void	check_exp_argv(t_exp_arg *av_lst, int *cnt_valid)
{
	int		i;
	int		k;

	i = 0;
	while (av_lst)
	{
		k = 0;
		while (av_lst->arg[k]
			&& (av_lst->arg[k] == '_' || ft_isalpha(av_lst->arg[k])))
			k++;
		if (!k || (ft_strchr(av_lst->arg, '=') && av_lst->arg[k] != '='))
		{
			exp_unset_invalid_arg_msg('e', av_lst->arg);
			av_lst->flag = 0;
		}
		else
			(*cnt_valid)++;
		av_lst = av_lst->next;
	}
}

static void	skip_or_sub_env(char ***ev, t_exp_arg *avs, char **to_fr, int *idx)
{
	t_exp_arg	*cur;
	char		*pos;

	while (to_fr[*idx + 1])
	{
		cur = avs->next;
		while (cur)
		{
			pos = ft_strchr(cur->arg, '=');
			if (!pos && !ft_strncmp(cur->arg, to_fr[*idx], ft_strlen(cur->arg)))
				cur->flag = 0;
			else if (pos && !ft_strncmp(cur->arg, to_fr[*idx], pos - cur->arg))
				break ;
			cur = cur->next;
		}
		if (cur)
		{
			*(*ev + *idx) = strdup_skip_qm(cur->arg, 0, 0);
			cur->flag = 0;
		}
		else
			*(*ev + *idx) = ft_strdup(to_fr[*idx]);
		(*idx)++;
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
	idx = 0;
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
	int			i;
	int			o_len;

	av_lst = NULL;
	cnt_val = 0;
	g_exit_code = EXIT_SUCCESS;
	o_len = ft_strsetlen((char **)(*envp));
	if (!argv[1])
		exprt_no_arg((char **)(*envp), o_len);
	else
	{
		av_lst = argv_to_lst((char **)argv);
		check_exp_argv(av_lst->next, &cnt_val);
		if (cnt_val)
			add_env((char ***)envp, av_lst, o_len + cnt_val);
	}
	if (av_lst)
		free_argv_lst(&av_lst);
	return (g_exit_code);
}
