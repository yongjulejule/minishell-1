/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:06:28 by ghan              #+#    #+#             */
/*   Updated: 2021/09/25 18:45:49 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern int	g_exit_code;

static void	cmds_lst_strtrim(t_cmds *cmds_hd)
{
	char	*to_free;
	t_cmds	*elem;

	elem = cmds_hd->next;
	while (elem)
	{
		to_free = ft_strdup(elem->cmd);
		elem->cmd = ft_strtrim(to_free, " \t\n");
		free(to_free);
		elem = elem->next;
	}
}

t_cmds	*parse_line_main(char *ln_read)
{
	t_cmds	*ret;
	t_cmds	*cmds_hd;
	char	*one_ln;

	one_ln = ft_strdup("");
	if (!read_internal_prompt(&one_ln, ln_read, 0))
	{
		if (g_exit_code == -42)
			g_exit_code = GEN_ERR;
		free(one_ln);
		return (NULL);
	}
	sub_env(&one_ln);
	cmds_hd = ps_lst_init(NULL);
	split_by_symbols(cmds_hd, one_ln);
	cmds_lst_strtrim(cmds_hd);
	if (!check_smcol_pipe_syntax(cmds_hd->next)
		|| !check_rdr_syntax(cmds_hd->next))
	{
		g_exit_code = 258;
		free_cmds_lst(&cmds_hd);
		return(NULL);
	}
	ret = cmds_hd->next;
	free(cmds_hd);
	return (ret);
}
