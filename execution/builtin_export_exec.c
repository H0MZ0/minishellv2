#include "execution.h"

int	execute_export(t_cmd *cmd, t_env **envp)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_key(cmd->args[i]))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else if (ft_strchr(cmd->args[i], '='))
			add_or_update_env(envp, cmd->args[i]);
		i++;
	}
	return (0);
}

