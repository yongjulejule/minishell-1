/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:06:28 by ghan              #+#    #+#             */
/*   Updated: 2021/09/21 13:52:49 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern int	g_exit_code;

static void	free_cmds_lst(t_cmds *cmds_hd)
{
	t_cmds	*elem;

	elem = cmds_hd;
	while (elem)
	{
		free(elem->cmd);
		elem = elem->next;
		free(cmds_hd);
		cmds_hd = elem;
	}
}

static char	**cmds_lst_to_arr(t_cmds *cmds_hd)
{
	char	**cmds_arr;
	char	*to_free;
	t_cmds	*elem;
	int		size;
	int		i;

	size = ps_lst_size(cmds_hd->next);
	cmds_arr = (char **)ft_calloc(size + 1, sizeof(char *));
	elem = cmds_hd->next;
	i = 0;
	while (elem)
	{
		to_free = ft_strdup(elem->cmd);
		cmds_arr[i++] = ft_strtrim(to_free, " \t\n");
		free(to_free);
		elem = elem->next;
	}
	free_cmds_lst(cmds_hd);
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
	// 	printf("%s\n", cmds_arr[i++]);
	// exit(1);
	// if (!check_smcol_pipe_syntax(cmds_arr))
	// {
	// 	free_cmds(cmds_arr);
	// 	cmds_arr = NULL;
	// }
	return (cmds_arr);
}
