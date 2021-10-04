/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:32:30 by ghan              #+#    #+#             */
/*   Updated: 2021/10/04 17:38:30 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*strchr_skip_bslash(const char *s, int c)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (*str != (unsigned char)c && *str != '\0')
	{
		if (*str == '\\')
			str++;
		if (*str != '\0')
			str++;
	}
	if (*str != (unsigned char)c)
		return (NULL);
	return ((char *)str);
}

void	is_qm(char *one_ln, char **qm)
{
	*qm = NULL;
	if (!(*qm) || (strchr_skip_bslash(one_ln, '\'')
			&& *qm > strchr_skip_bslash(one_ln, '\'')))
		*qm = strchr_skip_bslash(one_ln, '\'');
	if (!(*qm) || (strchr_skip_bslash(one_ln, '"')
			&& *qm > strchr_skip_bslash(one_ln, '"')))
		*qm = strchr_skip_bslash(one_ln, '"');
}
