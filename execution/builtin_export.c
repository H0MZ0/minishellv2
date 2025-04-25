#include "execution.h"

char	*extract_key(const char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	strncpy(key, str, i);
	key[i] = '\0';
	return (key);
}

char	*extract_value(const char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	return (ft_strdup(&str[i + 1]));
}

void	add_or_update_env(t_env **env, char *arg)
{
	t_env	*found;
	char	*key;
	char	*value;

	key = extract_key(arg);
	value = extract_value(arg);
	found = find_env(*env, key);
	if (found)
	{
		free(found->value);
		found->value = value;
	}
	else
	{
		t_env *new = malloc(sizeof(t_env));
		new->key = key;
		new->value = value;
		new->next = *env;
		*env = new;
	}
}
