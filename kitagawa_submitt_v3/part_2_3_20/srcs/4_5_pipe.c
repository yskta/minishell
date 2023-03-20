/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_5_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:30:15 by kohmatsu          #+#    #+#             */
/*   Updated: 2023/03/18 13:04:03 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	branch_do_v2(t_info *info, int i, int heredoc_count)
{
	if (ft_strcmp((info->argv)[i], "<<") == 0 && info->heredoc_flag == 0)
	{
		if (heredoc_count == 1)
			do_heredoc_one(info, i);
		else
			do_heredoc_not_one(info, i);
	}
	else if (*(info->argv)[i] == '<')
	{
		if (detect_something(info, i))
			return (1);
		do_input(info, i);
	}
	else if (*(info->argv)[i] == '>')
	{
		if (detect_something(info, i))
			return (1);
		do_output(info, i);
	}
	return (0);
}

int	branch_do_v1(t_info *info, int i, int heredoc_count)
{
	if (ft_strcmp((info->argv)[i], "<<") == 0 && info->heredoc_flag == 0)
	{
		branch_do_v2(info, i, heredoc_count);
		return (2);
	}
	else if (ft_strcmp((info->argv)[i], ">>") == 0)
	{
		do_append(info, i);
		return (2);
	}
	else if (*(info->argv)[i] == '<' || *(info->argv)[i] == '>')
	{
		if (branch_do_v2(info, i, heredoc_count))
			return (1);
		return (2);
	}
	return (0);
}

int	check_builtin(char *argv)
{
	if (ft_strcmp(argv, "cd") == 0)
		return (1);
	if (ft_strcmp(argv, "echo") == 0)
		return (1);
	if (ft_strcmp(argv, "env") == 0)
		return (1);
	if (ft_strcmp(argv, "exit") == 0)
		return (1);
	if (ft_strcmp(argv, "export") == 0)
		return (1);
	if (ft_strcmp(argv, "pwd") == 0)
		return (1);
	if (ft_strcmp(argv, "unset") == 0)
		return (1);
	return (0);
}

void	do_insert(t_info *info, int *pipe_index, int *argv_index, int end)
{
	char	**tmp;
	int		split_count;

	if (ft_strchr(info->cmd[*pipe_index], ' ') && g_signal.do_split)
	{
		split_count = 0;
		tmp = ft_split(info->cmd[*pipe_index], ' ');
		while (split_count < count_splitable(info, *pipe_index, end) + 1)
		{
			info->argv[*argv_index] = x_strdup(tmp[split_count]);
			split_count++;
			*argv_index += 1;
		}
		safty_free(tmp);
		*pipe_index += 1;
	}
	else
	{
		info->argv[*argv_index] = x_strdup(info->cmd[*pipe_index]);
		*argv_index += 1;
		*pipe_index += 1;
	}
}

void	make_info_argv(t_info *info, int end, int start)
{
	int		pipe_index;
	int		argv_index;

	argv_index = 0;
	if (info->argv)
		safty_free(info->argv);
	pipe_index = start + 1;
	info->argv_count = end - start + count_splitable(info, pipe_index, end);
	info->argv = x_double_str_malloc(info->argv_count);
	while (pipe_index < end)
		do_insert(info, &pipe_index, &argv_index, end);
	info->argv[argv_index] = NULL;
}