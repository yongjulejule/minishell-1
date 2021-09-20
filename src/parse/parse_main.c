/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:06:28 by ghan              #+#    #+#             */
/*   Updated: 2021/09/21 01:55:21 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern int	g_exit_code;

static char	**cmds_lst_to_arr(t_cmds *cmds_hd)
{
	char	**cmds_arr;
	t_cmds	*elem;
	int		size;
	int		i;

	size = ps_lst_size(cmds_hd->next);
	cmds_arr = (char **)ft_calloc(size + 1, sizeof(char *));
	elem = cmds_hd->next;
	i = 0;
	while (elem)
	{
		cmds_arr[i++] = ft_strdup(elem->cmd);
		elem = elem->next;
	}
	elem = cmds_hd;
	while (elem)
	{
		free(elem->cmd);
		elem = elem->next;
		free(cmds_hd);
		cmds_hd = elem;
	}
	return (cmds_arr);
}

char	**parse_line_main(char *ln_read)
{
	t_cmds	*cmds_hd;
	char	**cmds_arr;
	char	*one_ln;

	one_ln = ft_strdup("");
	if (!read_internal_prompt(&one_ln, ln_read, 0))
	{
		g_exit_code = 0;
		free(one_ln);
		return (NULL);
	}
	sub_env(&one_ln);
	cmds_hd = ps_lst_init(NULL);
	split_by_symbols(&cmds_hd, one_ln);
	cmds_arr = cmds_lst_to_arr(cmds_hd);
	// int i = 0;
	// while (cmds_arr[i])
	// 	printf("%s\n", cmds[i++]);
	// if (!check_smcol_pipe_syntax(cmds_arr))
	// {
	// 	free_cmds(cmds_arr);
	// 	cmds_arr = NULL;
	// }
	return (cmds_arr);
}
