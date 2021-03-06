/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:27:02 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/13 19:09:34 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	close_files(t_struct *st)
{
	if (st->was_chevr)
	{
		close(STDOUT_FILENO);
		st->was_chevr = 0;
		dup2(st->stdout_copy, 1);
	}
	if (st->was_lchevr)
	{
		close(STDIN_FILENO);
		st->was_lchevr = 0;
		dup2(st->stdin_copy, 0);
	}
}

static int	check_pipe(int nb, int total)
{
	if (nb == total)
		return (-1);
	else
		return (total);
}

static void	reset_in_out(int in, int out, t_struct *st)
{
	if (st->stdin_fd != 0)
		close(st->stdin_fd);
	st->stdin_fd = in;
	if (st->stdout_fd != 1)
		close(st->stdout_fd);
	st->stdout_fd = out;
}

static char	**cmd_before_pipe(char **cmd, int pipe_nb)
{
	char	**res;
	int		i;
	int		save;
	int		j;

	i = 0;
	while (pipe_nb > 0 && cmd[i])
	{
		if (!ft_strcmp(cmd[i], "|"))
			pipe_nb--;
		i++;
	}
	save = i;
	while (cmd[i] && ft_strcmp(cmd[i], "|"))
		i++;
	res = (char **)malloc(sizeof(char *) * (i - save + 1));
	j = 0;
	while (cmd[save] && ft_strcmp(cmd[save], "|"))
		res[j++] = ft_strdup(cmd[save++]);
	res[j] = NULL;
	return (res);
}

void	do_pipe(t_struct *st)
{
	int		new_pipe[2];
	int		pipe_nb;
	char	**cmd;

	pipe_nb = 0;
	while (pipe_nb <= st->pipe)
	{
		st->pipe = check_pipe(pipe_nb, st->pipe);
		if (pipe(new_pipe) != 0)
			return ;
		st->stdout_fd = new_pipe[1];
		cmd = cmd_before_pipe(st->cmd, pipe_nb);
		ft_edit_cmd(cmd);
		if (!do_chevrons(cmd, st))
		{
			cmd = del_chevron(cmd);
			if (ft_strcmp(cmd[0], ""))
				do_builtin(cmd, st);
			reset_in_out(new_pipe[0], 1, st);
		}
		ft_free_tab(cmd);
		close_files(st);
		pipe_nb++;
	}
	reset_in_out(0, 1, st);
}
