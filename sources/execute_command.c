#include "../includes/minishell.h"

static int	find_builtin_func(const char *word)
{
	char	*shell_builtins[7] = \
	{
		"echo", "exit", "unset", "export", "cd", "pwd", "env"
	};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(word, shell_builtins[i], ft_strlen(shell_builtins[i]) + 1))
			break ;
		++i;
	}
	return (i);
}

t_built_in_fp	is_builtin(char *word)
{
	//const는 나중에 없애도 볼것 
	const t_built_in_fp	builtin_func_table[7] = \ 
	{
		ft_echo, ft_exit, ft_unset, ft_export, ft_cd, ft_pwd, ft_env
	};
	int						idx;

	idx = find_builtin_func(word);
	if (idx > 6)
	{
		return (NULL);
	}
	return (builtin_func_table[idx]);
}

static int	execute_simple_internal(t_built_in_fp builtin, t_cmd *cmd)
{
	if (builtin)
	{
		list_remove_head_word(cmd->content.simple.words);
		return (builtin(cmd));
	}
	else
		execute_nonbuiltin(cmd, *cmd->envp_list); // 얘 아직 void
	return (0);
}

void	execute_command(t_all_data *all_data, t_cmd *cmd, int fd_info[3]) // all_data 받아와!!!
{
	int				return_value;
	t_word_data		*data;
	t_built_in_fp	built_in_fp;
	//int		wait_return;
	
	data = cmd->content.simple.words->head->data;
	if (is_builtin)
		built_in_fp = is_builtin(data->word);
	else
		built_in_fp = NULL;
	execute_simple_internal(built_in_fp, cmd);
	//이름 바꾸는 것도 괜찮을 듯. 이름이 어려버!
		//built_in();
	/* execute_nonbuiltin(cmd, all_data->envp_list);*/

	//return_value = execute_nonbuiltin(cmd, all_data.envp_list);
	// return_value = execute_command_internal(cmd, fd_info);
	// wait_return = ft_waitchild(cmd); 실행을 다 만든 다음에 진행할 예정
	// if (wait_return >= 0)
	// 	return_value = wait_return;
	// if (cmd->flag & CMD_FLAG_IS_FORKED)
	// 	exit(return_value);
	//return (return_value);
}
