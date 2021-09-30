/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_qm_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:36:13 by ghan              #+#    #+#             */
/*   Updated: 2021/09/30 12:37:08 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*strndup_with_flag(const char *s1, int *cp_flag, size_t n)
{
	char	*ret;
	size_t	len;
	size_t	i;
	size_t	k;

	i = 0;
	len = 0;
	while (i < n)
	{
		if (cp_flag[i] >= 0)
			len++;
		i++;
	}
	ret = (char *)ft_calloc(len + 1, 1);
	i = 0;
	k = 0;
	while (i < n)
	{
		if (cp_flag[i] >= 0)
			ret[k++] = s1[i];
		i++;
	}
	return (ret);
}

char	*get_first_word(char *str, int *cp_flag, size_t len)
{
	char	*ret;
	size_t	i;

	ret = NULL;
	i = 0;
	while (i < len)
	{
		if (cp_flag[i] == 2)
			break ;
		i++;
	}
	if (i != len)
		ret = strndup_with_flag(str, cp_flag, i);
	return (ret);
}

static void	flag_qm(char *str, int *i, int *cp_flag)
{
	char	*to_free;
	int		first;

	first = *i;
	skip_qmbt(str, i, "\"'");
	cp_flag[first] = IS_QM;
	cp_flag[*i] = IS_QM;
	to_free = ft_strndup(str + first, *i - first + 1);
	if (!ft_strchrset(to_free, " \n\t"))
	{
		cp_flag[first] = RM_QM;
		cp_flag[*i] = RM_QM;
	}
	free(to_free);
}

void	flag_cp_char(char *str, int *cp_flag)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += 2;
		else if (is_charset(str[i], "\"'"))
		{
			flag_qm(str, &i, cp_flag);
			i++;
		}
		else if (str[i])
		{
			if (is_charset(str[i], " \n\t"))
				cp_flag[i] = IS_WS;
			else if (str[i] == '=')
				cp_flag[i] = IS_EQ;
			i++;
		}
	}
}
