/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlastnstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 11:40:24 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/11 11:49:43 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	idx;
	size_t	size;

	if (!haystack)
		return (NULL);
	if (!needle || (*needle == '\0'))
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	idx = 0;
	size = ft_strlen(needle);
	while (0 <= len - size)
	{
		if (!ft_strncmp((char *)(haystack + len - size),
					(char *)(needle), size))
			return ((char *)(haystack + len - size));
		len--;
	}
	return (NULL);
}
