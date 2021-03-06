/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgimenez <lgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 21:52:11 by lgimenez          #+#    #+#             */
/*   Updated: 2021/06/14 18:02:03 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

void	cd_deltilde(char *path)
{
	int	i;

	if (path[0] == '~')
	{
		i = -1;
		while (path[++i])
			path[i] = path[i + 1];
	}
}

int	cd_getoldpwd(char **path, t_struct *st)
{
	t_varlist	*current;

	current = st->lst;
	while (current && ft_strcmp(current->name, "OLDPWD"))
		current = current->next;
	if (!current || !current->content)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 1);
		st->ret = 1;
		return (1);
	}
	*path = ft_strdup(current->content);
	return (0);
}
