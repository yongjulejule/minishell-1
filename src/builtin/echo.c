/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:53:44 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/23 13:04:39 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	echo(const char *path, char *const argv[], char *const envp[])
{
	int	idx;
	int	flag;

	flag = 0;
	idx = 0;
	if (!argv[1] && ft_strcmp(argv[1], "-n"))
		flag = 1;
	while (argv[idx + flag])
		printf("%s", argv[flag + idx++]);
	if (!flag)
		printf("\n");
	exit(EXIT_SUCCESS);
}
