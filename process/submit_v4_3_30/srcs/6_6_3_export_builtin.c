/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_6_3_export_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohmatsu <kohmatsu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:10:53 by yokitaga          #+#    #+#             */
/*   Updated: 2023/03/29 15:44:35 by kohmatsu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	yatto_owari(char **key, int *i)
{
	if (ft_strchr(*key, '$') != NULL)
	{
		*i += 1;
		free(*key);
		return (1);
	}
	free(*key);
	return (0);
}

bool	check_argv_no_such_env(t_info *info)
{
	int	i;

	i = 1;
	while (info->argv[i] != NULL)
	{
		if (ft_strchr(info->argv[i], '$') == NULL)
			return (false);
		i++;
	}
	return (true);
}

bool	check_add_or_not(char *arg)
{
	int		i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (true);
		i++;
	}
	return (false);
}

void	add_env_value(char *arg, t_environ *list)
{
	int			i;
	char		*key;
	t_environ	*head;

	i = ft_strchr_index(arg, '+');
	key = ft_strndup(arg, i);
	head = list;
	while (list != NULL)
	{
		if (ft_strcmp(list->key, key) == 0)
		{
			list->value = ft_strjoin_with_free(list->value,
					arg + i + 2, FIRST_PARAM);
			break ;
		}
		list = list->next;
	}
	if (list == NULL)
		list_add_back_export(&head, key, &arg[i + 2]);
	free(key);
}

int	not_allowed_variant_character(char *key)
{
	if (ft_strcmp(key, "") == 0)
		return (1);
	if (key[0] == '$')
		return (0);
	while (*key)
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (1);
		key++;
	}
	return (0);
}
