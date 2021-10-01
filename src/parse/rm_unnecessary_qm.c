/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_unnecessary_qm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:10:29 by ghan              #+#    #+#             */
/*   Updated: 2021/10/01 20:31:19 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	push_qm(char *str, int is_exp, int *first, int *second)
{
	int	len;

	len = (int)ft_strlen(str);
	while (*first >= 1)
	{
		if (*first > 1 && str[*first - 1] == '&'
			&& is_charset(str[*first - 2], "<>"))
			break ;
		if (!is_exp && !is_charset(str[*first - 1], NOT_EXP_CSET))
			swap_char(&str[*first], &str[*first - 1]);
		else if (is_exp && !is_charset(str[*first - 1], IS_EXP_CSET))
			swap_char(&str[*first], &str[*first - 1]);
		else
			break ;
		(*first)--;
	}
	while (*second + 1 < len)
	{
		if (!is_charset(str[*second + 1], NOT_EXP_CSET))
			swap_char(&str[*second], &str[*second + 1]);
		else
			break ;
		(*second)++;
	}
}

static void	rm_or_expand_qm(t_cmds *cur, int *cp_flag, int is_exp, int len)
{
	char	*to_free;
	char	qm;
	int		first;
	int		second;

	to_free = cur->cmd;
	cur->cmd = strndup_with_flag(cur->cmd, cp_flag, len);
	free(to_free);
	len = ft_strlen(cur->cmd);
	second = 0;
	while (strchrset_skip_bs(cur->cmd + second, "\"'"))
	{
		qm = *strchrset_skip_bs(cur->cmd + second, "\"'");
		first = strchrset_skip_bs(cur->cmd + second, "\"'") - cur->cmd;
		second = strchr_skip_bslash(cur->cmd + first + 1, qm) - cur->cmd;
		push_qm(cur->cmd, is_exp, &first, &second);
		second++;
	}
}

void	rm_unnecessary_qm(t_cmds *cmds_hd)
{
	t_cmds	*cur;
	char	*first_wd;
	int		*cp_flag;
	int		is_exp;
	size_t	len;

	cur = cmds_hd->next;
	while (cur)
	{
		if (ft_strchrset(cur->cmd, "\"'"))
		{
			len = ft_strlen(cur->cmd);
			cp_flag = (int *)ft_calloc(len, sizeof(int));
			flag_cp_char(cur->cmd, cp_flag);
			first_wd = get_first_word(cur->cmd, cp_flag, len);
			is_exp = 0;
			if (first_wd && !ft_strcmp(first_wd, "export"))
				is_exp = 1;
			free(first_wd);
			rm_or_expand_qm(cur, cp_flag, is_exp, len);
			free(cp_flag);
		}
		cur = cur->next;
	}
}
