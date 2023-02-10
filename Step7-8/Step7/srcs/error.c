/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:33:51 by yokitaga          #+#    #+#             */
/*   Updated: 2023/02/10 23:24:34 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/step_7_8.h"

bool	syntax_error = false;

void fatal_error(const char *msg)
{
    dprintf(STDERR_FILENO, "Fatal Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

void	err_exit(const char *location, const char *msg, int status)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, msg);
	exit(status);
}

void	assert_error(const char *msg)
{
	dprintf(STDERR_FILENO, "Assert Error: %s\n", msg);
	exit(255);
}

void	todo(const char *msg)
{
	dprintf(STDERR_FILENO, "TODO: %s\n", msg);
	exit(255);
}

void tokenize_error(const char *location, char **rest, char *line)
{
	syntax_error = true;
	dprintf(STDERR_FILENO, "minishell: syntax error near %s\n", location);
	while (*line)
		line++;
	*rest = line;
}