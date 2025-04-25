#include "execution.h"

int	execute_unset(t_cmd *cmd, t_env **envp)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (is_valid_key(cmd->args[i]))
			remove_env_var(envp, cmd->args[i]);
		else
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		i++;
	}
	return (0);
}
