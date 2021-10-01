/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchrset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 15:16:02 by ghan              #+#    #+#             */
/*   Updated: 2021/10/01 16:19:18 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchrset(const char *s, char *charset)
{
	char	*str;
	int		len;
	int		k;

	if (!s || !charset)
		return (NULL);
	len = ft_strlen(s);
	str = (char *)s;
	while (len > 0)
	{
		k = -1;
		while (charset[++k])
			if (*(str + len) == charset[k])
				return (str + len);
		len--;
	}
	k = -1;
	while (charset[++k])
		if (*str == charset[k])
			return (str);
	return (NULL);
}
