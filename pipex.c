/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:46:29 by ngobert           #+#    #+#             */
/*   Updated: 2022/02/09 18:01:49 by ngobert          ###   ########.fr       */
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
}

void	child1_exec(t_data *data, char *cmd)
{
	if (dup2(data->infile, STDIN_FILENO) == -1)
		ft_error("dup2 failed\n");
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		ft_error("dup2 failed\n");
	close(data->fd[0]);
	close(data->infile);
	exec_cmd(data, cmd);
}

void	child2_exec(t_data *data, char *cmd)
{
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		ft_error("dup2 failed\n");
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		ft_error("dup2 failed\n");
	close(data->fd[1]);
	close(data->outfile);
	exec_cmd(data, cmd);
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
	if (data->child_1 == 0)
		child2_exec(data, cmd2);
	close_and_wait(data);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;
	if (argc != 5)
		ft_error("Too much args");	
	else
	{
		data = get_args(argc, argv, envp);
		data.infile = open(argv[1], O_RDONLY);
		data.outfile = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY);
		if (!data.infile || !data.outfile)
			ft_error("Problem opening files\n");
		ft_pipex(&data, argv[1], argv[2]);
	}
}
