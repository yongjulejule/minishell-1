/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:06:28 by ghan              #+#    #+#             */
/*   Updated: 2021/09/29 12:07:30 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern int	g_exit_code;

void	parse_line_main(t_cmds **cmds_hd, char *ln_read,
			char **ft_envp, char *one_ln)
{
	t_cmds	*to_free;

	if (!read_internal_prompt(&one_ln, ln_read, 0))
	{
		if (g_exit_code == -42)
			g_exit_code = GEN_ERR;
		free(one_ln);
		*cmds_hd = NULL;
		return ;
	}
	sub_env(&one_ln, ft_envp);
	*cmds_hd = ps_lst_init(NULL);
	split_by_symbols((*cmds_hd), one_ln);
	if (!check_smcol_pipe_syntax((*cmds_hd)->next)
		|| !check_rdr_syntax((*cmds_hd)->next))
	{
		g_exit_code = 258;
		free_cmds_lst(cmds_hd);
		return ;
	}
	to_free = *cmds_hd;
	*cmds_hd = (*cmds_hd)->next;
	free(to_free);
}
