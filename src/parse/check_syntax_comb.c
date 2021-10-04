/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_comb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:41:01 by ghan              #+#    #+#             */
/*   Updated: 2021/10/04 17:48:34 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	syntax_error_cases(t_cmds *elem, char **symbols)
{
	if (is_strset(elem->cmd, symbols) && !ft_strcmp(elem->next->cmd, ";"))
	{
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `;'",
			STDERR_FILENO);
		return (0);
	}
	else if (!elem->next->next && !ft_strcmp(elem->cmd, ">")
		&& !ft_strcmp(elem->next->cmd, "|"))
	{
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		return (0);
	}
	else if (is_strset(elem->cmd, symbols) && !ft_strcmp(elem->next->cmd, "|"))
	{
		ft_putendl_fd("🤣 esh: syntax error near unexpected token `|'",
			STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	check_syntax_combination(t_cmds *elem)
{
	char	*symbols[9];

	init_symbols(symbols);
	while (elem->next)
	{
		if (!syntax_error_cases(elem, symbols))
			return (0);
		elem = elem->next;
	}
	return (1);
}
