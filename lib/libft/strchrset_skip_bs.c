/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchrset_skip_bs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 17:19:40 by ghan              #+#    #+#             */
/*   Updated: 2021/10/03 20:28:36 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strchrset_skip_bs(const char *s, char *charset)
{
	unsigned char	*str;

	if (!s || !charset || !(*s) || !(*charset))
		return (NULL);
	str = (unsigned char *)s;
	while (!is_charset(*str, charset) && (*str != '\0'))
	{
		if (*str == '\\')
			str++;
		if (*str != '\0')
			str++;
	}
	if (!is_charset(*str, charset))
		return (NULL);
	return ((char *)str);
}
