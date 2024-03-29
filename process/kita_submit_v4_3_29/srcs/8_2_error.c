/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_2_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:42:10 by yokitaga          #+#    #+#             */
/*   Updated: 2023/03/21 12:04:38 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	assert_error(const char *msg)
{
	my_dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

void	err_exit(const char *location, const char *msg)
{
	my_dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, msg);
	exit(127);
}

void	command_not_found(const char *location)
{
	my_dprintf(STDERR_FILENO, "minishell: %s: command not found\n", location);
	exit(127);
}

void	file_not_found(const char *filename)
{
	my_dprintf(STDERR_FILENO, "minishell: %s:\
No such file or directory\n", filename);
}

void	ambiguous_redirect(char *filename)
{
	my_dprintf(STDERR_FILENO, "minishell: %s: ambiguous redirect\n", filename);
}
