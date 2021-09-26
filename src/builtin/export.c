/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 10:36:58 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/26 18:55:36 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

// static int	check_argv_validity(char **av)
// {
// 	int	idx;


// }

static void	swap_str(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static void	exprt_no_arg(char **envp, int len)
{
	char	**in_order;
	int		i;
	int		k;

	in_order = dup_envp(envp, len);
	i = -1;
	while (++i + 1 < len)
	{
		k = i;
		while (++k < len)
		{
			if (ft_strcmp(in_order[i], in_order[k]) > 0)
				swap_str(&in_order[i], &in_order[k]);
		}
	}
	i = 0;
	while (in_order[i])
		printf("declare -x %s\n", in_order[i++]);
	free_double_ptr((void ***)(&in_order));
}

int	exprt(const char *path, char *const argv[], char *const envp[])
{
	if (!argv[1])
		exprt_no_arg((char **)envp, ft_strsetlen((char **)envp));
	// if (!check_argv_validity((char **)argv))
	// 	return ();
	return (0);
}
