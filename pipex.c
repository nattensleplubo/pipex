/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:46:29 by ngobert           #+#    #+#             */
/*   Updated: 2022/02/12 13:29:01 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char *argv, t_data *data)
{
	char	**paths;
	char	**cmd;
	char	*bin;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		ft_error("Split failed\n");
	paths = get_paths(data);
	bin = get_bin(cmd[0], paths);
	if (execve(bin, cmd, data->envp) == -1)
	{
		free(bin);
		ft_free(cmd);
		ft_error("Failed execution (execve returned -1)");
	}
}

void	child1_exec(t_data *data, char *cmd)
{
	if ((dup2(data->infile, STDIN_FILENO)) == -1)
		ft_error("dup2 failed\n");
	if ((dup2(data->fd[1], STDOUT_FILENO)) == -1)
		ft_error("dup2 failed\n");
	close(data->fd[0]);
	close(data->infile);
	exec_cmd(cmd, data);
}

void	child2_exec(t_data *data, char *cmd)
{
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		ft_error("dup2 failed\n");
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		ft_error("dup2 failed\n");
	close(data->fd[1]);
	close(data->outfile);
	exec_cmd(cmd, data);
}

void	ft_pipex(t_data *data, char *cmd1, char *cmd2)
{
	if (pipe(data->fd) == -1)
		ft_error("Failed opening the pipe\n");
	data->child_1 = fork();
	if (data->child_1 == -1)
		ft_error("Failed forkink for child 1\n");
	if (data->child_1 == 0)
		child1_exec(data, cmd1);
	data->child_2 = fork();
	if (data->child_2 == -1)
		ft_error("Failed forking for child 2\n");
	if (data->child_2 == 0)
		child2_exec(data, cmd2);
	close_and_wait(data);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;

	i = 1;
	if (argc < 5)
		ft_error("Too much args");
	else
	{
		data = get_args(argc, argv, envp);
		data.infile = open(argv[1], O_RDONLY);
		data.outfile = open(argv[argc - 1], O_CREAT
				| O_TRUNC | O_WRONLY, 0644);
		if (data.infile < 0 || data.outfile < 0)
			ft_error("Problem opening files\n");
		while (++i < data.argc - 2)
		{
			ft_pipex(&data, argv[i], argv[i + 1]);
		}
	}
}
