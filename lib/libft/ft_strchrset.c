/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:02:58 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/18 11:07:32 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrset(const char *s, char *charset)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (!is_charset(*str, charset) && (*str != 0))
		str++;
	if (!is_charset(*str, charset))
		return (NULL);
	return ((char *)str);
}
