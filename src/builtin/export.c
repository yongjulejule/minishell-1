/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 10:36:58 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/07 22:08:03 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

static int	get_cmp_len(char *arg, char *var, size_t *len, int *cat_flag)
{
	char	*pos_a;
	char	*pos_v;
	size_t	eq_idx_a;
	size_t	eq_idx_v;

	pos_a = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (!pos_a)
		pos_a = ft_strchr(arg, '=');
	else
		*cat_flag = 1;
	pos_v = ft_strchr(var, '=');
	if (pos_a)
		eq_idx_a = pos_a - arg;
	else
		eq_idx_a = ft_strlen(arg);
	if (pos_v)
		eq_idx_v = pos_v - var;
	else
		eq_idx_v = ft_strlen(var);
	*len = eq_idx_v;
	if (eq_idx_a > eq_idx_v)
		*len = eq_idx_a;
	if (pos_a)
		return (1);
	return (0);
}

static void	flag_argv(t_exp_arg **cur, char *var)
{
	size_t	len;
	int		pos;
	int		cat_flag;

	cat_flag = 0;
	len = 0;
	while (*cur)
	{
		pos = get_cmp_len((*cur)->arg, var, &len, &cat_flag);
		if (cat_flag)
			(*cur)->flag = 2;
		if ((*cur)->flag && !pos && !ft_strncmp((*cur)->arg, var, len))
			(*cur)->flag = 0;
		else if ((*cur)->flag && pos && !ft_strncmp((*cur)->arg, var, len))
			break ;
		*cur = (*cur)->next;
	}
}

static void	skip_or_sub_env(char ***ev, t_exp_arg *avs, char *env, int i)
{
	t_exp_arg	*cur;
	char		*tf;

	cur = avs->next;
	flag_argv(&cur, env);
	if (cur && cur->flag)
	{
		if (cur->flag == 1)
			*(*ev + i) = strdup_skip_qm(cur->arg, 0, 0);
		else if (cur->flag == 2)
		{
			tf = strdup_skip_qm(cur->arg, 0, 0);
			if (ft_strchr(env, '='))
				*(*ev + i) = ft_strjoin(env, ft_strchr(tf, '=') + 1);
			else
				*(*ev + i) = ft_strjoin(env, ft_strchr(tf, '='));
			free(tf);
		}
		cur->flag = 0;
	}
	else
		*(*ev + i) = ft_strdup(env);
}

static void	add_env(char ***ev, t_exp_arg *avs, int new_len)
{
	char		**to_fr;
	int			idx;
	t_exp_arg	*cur;

	to_fr = *ev;
	*ev = (char **)ft_calloc(new_len + 1, sizeof(char *));
	idx = -1;
	while (to_fr[++idx])
		skip_or_sub_env(ev, avs, to_fr[idx], idx);
	cur = avs->next;
	while (cur)
	{
		if (cur->flag)
			*(*ev + idx++) = strdup_skip_qm(cur->arg, 0, 0);
		cur = cur->next;
	}
	free_double_ptr((void ***)&to_fr);
}

int	exprt(const char *path, char *const argv[], char ***const envp)
{
	t_exp_arg	*av_lst;
	int			cnt_val;
	int			o_len;

	if (!path || !argv || !envp)
	{
		g_exit_code = is_error_no_exit("export : ", NULL,
				"pass valid args to builtin functions", EXIT_FAILURE);
		return (g_exit_code);
	}
	cnt_val = 0;
	g_exit_code = EXIT_SUCCESS;
	o_len = ft_strsetlen((char **)(*envp));
	if (!argv[1])
		exprt_no_arg((char **)(*envp), o_len);
	else
	{
		av_lst = argv_to_lst((char **)argv, 0);
		check_exp_argv(av_lst, &cnt_val);
		check_var_overlap(av_lst);
		if (cnt_val)
			add_env((char ***)envp, av_lst, o_len + cnt_val);
		free_argv_lst(&av_lst);
	}
	return (g_exit_code);
}
