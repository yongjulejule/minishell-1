/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 00:29:16 by ghan              #+#    #+#             */
/*   Updated: 2021/10/01 21:25:49 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

char	*strdup_skip_qm(char *s, size_t idx, size_t cnt_skip)
{
	char	*tmp;
	char	qm;
	size_t	n_idx;

	while (*(s + idx))
	{
		qm = *(s + idx++);
		if (is_charset(qm, "\"'"))
		{
			cnt_skip = 2;
			break ;
		}
		else
			qm = '\0';
	}
	tmp = (char *)ft_calloc(ft_strlen(s)
			- cnt_skip + 1, sizeof(char));
	idx = -1;
	n_idx = 0;
	while (*(s + ++idx))
	{
		if (*(s + idx) != qm)
			*(tmp + n_idx++) = *(s + idx);
	}
	return (tmp);
}

void	append_env_var(char ***envp, char *arg, int *n_idx)
{
	int	k;

	k = 0;
	while (arg[k] && (arg[k] == '_' || ft_isalpha(arg[k])))
		k++;
	if (k && (!ft_strchr(arg, '=')
			|| (ft_strchr(arg, '=') && arg[k] == '=')))
		*(*envp + (*n_idx)++) = strdup_skip_qm(arg, 0, 0);
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
