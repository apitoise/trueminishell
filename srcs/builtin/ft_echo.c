/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:24:06 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/31 10:28:00 by apitoise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

int	ft_echo(char **cmd, t_struct *st)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd[i] && !ft_strcmp(cmd[i], "-n"))
	{
		i++;
		n++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], st->stdout_fd);
		if (cmd[i + 1])
			ft_putstr_fd(" ", st->stdout_fd);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", st->stdout_fd);
	st->ret = 0;
	return (0);
}
