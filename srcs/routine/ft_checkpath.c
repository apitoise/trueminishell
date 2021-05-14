/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkpath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:26:41 by apitoise          #+#    #+#             */
/*   Updated: 2021/05/14 16:57:44 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	ft_freepathtab(char **pathtab)
{
	int	i;

	i = 0;
	while (pathtab[i])
	{
		free(pathtab[i]);
		pathtab[i] = NULL;
		i++;
	}
	free(pathtab);
	pathtab = NULL;
}

static int	ft_checkfile(char *filepath)
{
	struct stat	buff;

	return (!stat(filepath, &buff));
}

static char	*ft_finalpath(char *s1, char *s2)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(s1, "/");
	tmp2 = ft_strjoin(tmp1, s2);
	free(tmp1);
	return (tmp2);
}

static void	ft_checkpath2(char **cmd, char *path, t_struct *st)
{
	char	**pathtab;
	char	*filepath;
	int		i;

	pathtab = ft_split(path, ':');
	filepath = NULL;
	i = 0;
	while (pathtab[i])
	{
		filepath = ft_finalpath(pathtab[i], cmd[0]);
		if (ft_checkfile(filepath))
		{
			ft_exec(cmd, filepath, st);
			free(filepath);
			return ;
		}
		else
		{
			free(filepath);
			filepath = NULL;
			i++;
		}
	}
	ft_freepathtab(pathtab);
	not_cmd(cmd[0], st);
}

void		ft_checkpath(char **cmd, t_struct *st)
{
	t_varlist	*tmp;

	tmp = st->lst;
	while (tmp && ft_strcmp(tmp->name, "PATH"))
		tmp = tmp->next;
	if (!tmp)
		not_cmd(cmd[0], st);
	else
		ft_checkpath2(cmd, tmp->content, st);
}
