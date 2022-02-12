/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:45:21 by ngobert           #+#    #+#             */
/*   Updated: 2022/02/12 12:45:49 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_and_wait(t_data *data)
{
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(data->child_1, NULL, 0);
	waitpid(data->child_2, NULL, 0);
}

char	*get_bin(char *cmd, char **paths)
{
	char	*tmp;
	char	*ret_path;
	int		i;

	tmp = NULL;
	ret_path = NULL;
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		ret_path = ft_strjoin(tmp, cmd);
		if (access(ret_path, F_OK) == 0)
			return (ret_path);
		free(ret_path);
	}
	ft_error("Command not found\n");
	return (NULL);
}

char	*get_line(t_data *data)
{
	char	*path;
	int		i;

	i = -1;
	path = NULL;
	while (data->envp[++i])
	{
		path = ft_strnstr(data->envp[i], "PATH=/", ft_strlen(data->envp[i]));
		if (path)
		{
			path = ft_substr(path, 5, ft_strlen(path));
			if (!path)
				ft_error("Substr failed :(\n");
			return (path);
		}
	}
	return (NULL);
}

char	**get_paths(t_data *data)
{
	char	*str;
	char	**paths;

	str = get_line(data);
	paths = ft_split(str, ':');
	if (!paths)
		ft_error("Split failed\n");
	return (paths);
}
