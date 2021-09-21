/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:15:16 by ghan              #+#    #+#             */
/*   Updated: 2021/09/22 00:34:11 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	check_one_str(char *str)
{
	if (!ft_strcmp(";", str))
	{
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `;'",
			STDERR_FILENO);
		return (0);
	}
	else if (!ft_strcmp("|", str))
	{
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `|'",
			STDERR_FILENO);
		return (0);
	}
	return (1);
}

static void	write_pp_sm_error(char *first, char *secnd)
{
	if (!ft_strcmp("|", first))
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `|'",
			STDERR_FILENO);
	else if (!ft_strcmp(";", first) && !ft_strcmp(";", secnd))
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `;;'",
			STDERR_FILENO);
	else if ((!ft_strcmp("", first) && !ft_strcmp(";", secnd))
		|| (!ft_strcmp(";", first) && !ft_strcmp("|", secnd)))
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `;'",
			STDERR_FILENO);
	else if (!ft_strcmp("|", first) && !ft_strcmp("|", secnd))
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `||'",
			STDERR_FILENO);
	else if ((!ft_strcmp("", first) && !ft_strcmp("|", secnd))
		|| (!ft_strcmp("|", first) && !ft_strcmp(";", secnd)))
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `|'",
			STDERR_FILENO);
}

int	check_smcol_pipe_syntax(char **cmds)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (cmds[len])
		len++;
	i = 0;
	while (i + 1 < len)
	{
		if ((!ft_strcmp(";", cmds[i]) && !ft_strcmp(";", cmds[i + 1]))
			|| (!ft_strcmp("", cmds[i]) && !ft_strcmp(";", cmds[i + 1]))
			|| (!ft_strcmp("|", cmds[i]) && !ft_strcmp("|", cmds[i + 1]))
			|| (!ft_strcmp("", cmds[i]) && !ft_strcmp("|", cmds[i + 1]))
			|| (!ft_strcmp(";", cmds[i]) && !ft_strcmp("|", cmds[i + 1]))
			|| (!ft_strcmp("|", cmds[i]) && !ft_strcmp(";", cmds[i + 1]))
			|| (!ft_strcmp("|", cmds[0])))
		{
			write_pp_sm_error(cmds[i], cmds[i + 1]);
			return (0);
		}
		i++;
	}
	if (!i && !check_one_str(cmds[0]))
		return (0);
	return (1);
}

static void	write_cons_rdr_error(char *str)
{
	char	*to_free;
	int		len;

	len = 1;
	if ((*str == '>' && is_charset(*(str + 1), ">&"))
		|| (is_charset(*str, "<&") && is_charset(*(str + 1), "<>&")))
		len++;
	to_free = strndup(str, len);
	ft_putstr_fd("🤣 esh: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(to_free, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	free(to_free);
}

int	check_rdr_syntax(char **cmds)
{
	char	*symbols[11];
	int		len;
	int		i;

	init_symbols(symbols);
	len = cmds_arr_len(cmds);
	if (is_strset(cmds[len - 1], symbols)
		|| is_strset_end(cmds[len - 1], symbols))
	{
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		return (0);
	}
	i = -1;
	while (len > 1 && cmds[++i + 1])
	{
		if ((is_strset(cmds[i], symbols)
				|| is_strset_end(cmds[i], symbols))
			&& (is_charset(*cmds[i + 1], "<>&")))
		{
			write_cons_rdr_error(cmds[i + 1]);
			return (0);
		}
	}
	return (1);
}
