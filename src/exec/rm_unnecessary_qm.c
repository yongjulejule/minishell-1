/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_unnecessary_qm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:10:29 by ghan              #+#    #+#             */
/*   Updated: 2021/10/09 01:42:45 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	push_qm(char **str, int *first, int *second)
{
	int	len;

	len = (int)ft_strlen(*str);
	while (*first >= 1)
	{
		if (*first > 2 && *(*str + *first - 1) == '&'
			&& is_charset(*(*str + *first - 2), "<>"))
			break ;
		if (!is_charset(*(*str + *first - 1), SWAP_CSET))
			swap_char((*str + *first), (*str + *first - 1));
		else
			break ;
		(*first)--;
	}
	while (*second + 1 < len)
	{
		if (!is_charset(*(*str + *second + 1), SWAP_CSET))
			swap_char((*str + *second), (*str + *second + 1));
		else
			break ;
		(*second)++;
	}
}

static int	skip_inner_qm(char *first, char *second)
{
	char	*to_fr;
	int		ret;

	ret = 0;
	to_fr = ft_strndup(first, second - first);
	if (ft_strchrset(to_fr, " \n\t"))
		ret = 1;
	free(to_fr);
	return (ret);
}

static void	rm_or_expand_qm(char **param, int *cp_flag, size_t len, size_t add)
{
	char	qm;
	int		first;
	int		second;
	char	*to_fr;

	to_fr = *param;
	*param = strndup_with_flag(*param, cp_flag, len, add);
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
		if (skip_inner_qm(*param + first + 1, *param + second))
			push_qm(param, &first, &second);
		second++;
	}
}

static size_t	flag_cp_char(char *str, int *cp_flag)
{
	int		i;
	size_t	add_cnt;

	add_cnt = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += 2;
		else if (is_charset(str[i], "\"'"))
		{
			flag_qm(str, &i, cp_flag, &add_cnt);
			i++;
		}
		else if (str[i])
			i++;
	}
	return (add_cnt);
}

void	rm_unnecessary_qm(char **param)
{
	int		*cp_flag;
	size_t	add_cnt;
	size_t	len;

	len = ft_strlen(*param);
	cp_flag = (int *)ft_calloc(len, sizeof(int));
	add_cnt = flag_cp_char(*param, cp_flag);
	rm_or_expand_qm(param, cp_flag, len, add_cnt);
	free(cp_flag);
}
