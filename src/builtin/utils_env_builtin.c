/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 00:29:16 by ghan              #+#    #+#             */
/*   Updated: 2021/10/07 22:16:11 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

static void	skip_qm_plus_cpy(char **ret, char *s, char qm)
{
	int	idx;
	int	n_idx;
	int	eq_flag;

	eq_flag = 0;
	n_idx = 0;
	idx = -1;
	while (*(s + ++idx))
	{
		if (*(s + idx) == '=')
			eq_flag = 1;
		if (*(s + idx) != qm && !(*(s + idx) == '+' && !eq_flag))
			*(*ret + n_idx++) = *(s + idx);
	}
}

char	*strdup_skip_qm(char *s, size_t idx, size_t cnt_skip)
{
	char	*ret;
	char	qm;
	int		eq_flag;

	eq_flag = 0;
	while (*(s + idx))
	{
		qm = *(s + idx++);
		if (qm == '=')
			eq_flag = 1;
		if (is_charset(qm, "\"'") || (!eq_flag && qm == '+'))
		{
			if (!eq_flag && qm == '+')
				cnt_skip++;
			else
				cnt_skip += 2;
			break ;
		}
		else
			qm = '\0';
	}
	ret = (char *)ft_calloc(ft_strlen(s)
			- cnt_skip + 1, sizeof(char));
	skip_qm_plus_cpy(&ret, s, qm);
	return (ret);
}

t_exp_arg	*argv_to_lst(char **argv, int i)
{
	t_exp_arg	*hd;

	hd = exp_lst_init(NULL);
	while (argv[++i])
		exp_lst_addback(hd, exp_lst_init(ft_strdup(argv[i])));
	return (hd);
}

void	exp_unset_invalid_arg_msg(char c, char *str)
{
	if (c == 'e')
		ft_putstr_fd("🤣 esh: export: `", STDERR_FILENO);
	else if (c == 'u')
		ft_putstr_fd("🤣 esh: unset: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	g_exit_code = EXIT_FAILURE;
}

void	exprt_no_arg(char **envp, int len)
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
