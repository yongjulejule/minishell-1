/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:53:44 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/26 16:48:33 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_code;

int	echo(const char *path, char *const argv[], char *const envp[])
{
	int	idx;
	int	flag;

	flag = 1;
	idx = 0;
	if (!argv[1] || !ft_strcmp(argv[1], "-n"))
		flag = 2;
	while (argv[idx + flag])
		printf("%s", argv[flag + idx++]);
	if (flag != 2)
		printf("\n");
	g_exit_code = 0;
	return (0);
}
