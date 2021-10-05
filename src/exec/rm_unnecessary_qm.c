/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_unnecessary_qm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:10:29 by ghan              #+#    #+#             */
/*   Updated: 2021/10/05 14:14:11 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	push_qm(char **str, int is_exp, int *first, int *second)
{
	int	len;

	len = (int)ft_strlen(*str);
	while (*first >= 1)
	{
		if (*first > 2 && *(*str + *first - 1) == '&'
			&& is_charset(*(*str + *first - 2), "<>"))
			break ;
		if (!is_exp && !is_charset(*(*str + *first - 1), NOT_EXP_CSET))
			swap_char((*str + *first), (*str + *first - 1));
		else if (is_exp && !is_charset(*(*str + *first - 1), IS_EXP_CSET))
			swap_char((*str + *first), (*str + *first - 1));
		else
			break ;
		(*first)--;
	}
	while (*second + 1 < len)
	{
		if (!is_charset(*(*str + *second + 1), NOT_EXP_CSET))
			swap_char((*str + *second), (*str + *second + 1));
		else
			break ;
		(*second)++;
	}
}

static void	rm_or_expand_qm(char **param, int *cp_flag, int is_exp, int len)
{
	char	qm;
	int		first;
	int		second;
	char	*to_fr;

	to_fr = *param;
	*param = strndup_with_flag(*param, cp_flag, len);
	free(to_fr);
	second = 0;
	while (*(*param + second) && strchrset_skip_bs(*param + second, "\"'"))
	{
		qm = *strchrset_skip_bs(*param + second, "\"'");
		first = strchr_skip_bslash(*param + second, qm) - *param;
		if (!strchr_skip_bslash(*param + first + 1, qm))
			break ;
		second = strchr_skip_bslash(*param + first + 1, qm) - *param;
		if (*(*param + second) == '\0')
			break ;
		push_qm(param, is_exp, &first, &second);
		second++;
	}
}

void	rm_unnecessary_qm(char **param)
{
	char	*first_wd;
	char	*to_fr;
	int		*cp_flag;
	int		is_exp;
	size_t	len;

	len = ft_strlen(*param);
	cp_flag = (int *)ft_calloc(len, sizeof(int));
	flag_cp_char(*param, cp_flag);
	first_wd = get_first_word(*param, cp_flag, len);
	is_exp = 0;
	if (first_wd && !ft_strcmp(first_wd, "export"))
		is_exp = 1;
	free(first_wd);
	to_fr = *param;
	rm_or_expand_qm(param, cp_flag, is_exp, len);
	free(cp_flag);
}
