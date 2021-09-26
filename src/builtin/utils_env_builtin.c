/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 00:29:16 by ghan              #+#    #+#             */
/*   Updated: 2021/09/27 02:11:44 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

t_exp_arg	*argv_to_lst(char **argv)
{
	t_exp_arg	*hd;
	int			i;

	hd = exp_lst_init(NULL);
	i = 0;
	while (argv[++i])
		exp_lst_addback(hd, exp_lst_init(ft_strdup(argv[i])));
	return (hd);
}
