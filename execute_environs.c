#ifndef __EXECUTE_ENVIRONS__
#define __EXECUTE_ENVIRONS__

#include "shell.h"

/**
 * retrieve_environment_variable_value - retrieves the value of a specific environment variable.
 *
 * This function searches for the environment variable with the specified name
 * within the provided list of environment variables. It iterates through
 * the list, comparing each variable name with the specified name using
 * string_prefix_equal().
 * If a match is found, the function returns a pointer to the
 * value of the variable.
 * If no match is found, NULL is returned.
 *
 * @environment_info: A pointer to the structure containing environment variables.
 * @variable_name: The identifier of the environment variable to retrieve.
 *
 * Return: Upon success, a pointer to the value of the
 * specified environment variable.
 * If the specified environment variable is not found, NULL is returned.
 */
char *retrieve_environment_variable_value(info_t *environment_info, const char *variable_name)
{
	list_t *current_node = environment_info->env;
	char *variable_value;

	while (current_node)
	{
		variable_value = string_starts_with(current_node->str, variable_name);
		if (variable_value && *variable_value)
			return (variable_value);
		current_node = current_node->next;
	}
	return (NULL);
}

/**
 * set_or_update_environment_variable - sets or updates an environment variable.
 * This function sets or updates an environment variable in the
 * current process.
 * It allocates memory to construct the environment variable string
 * in the format "name=value".
 * If either @variable_name or @variable_value is NULL, the function returns without
 * modifying the environment.
 * If memory allocation fails, the function returns 1, indicating failure.
 * If the environment variable already exists, its value is updated.
 * If the environment variable doesn't exist, it is added to the environment
 * list.
 * The info->environ_changed flag is set to 1 to indicate that the
 * environment has been modified.
 *
 * @info: A pointer to the info_t structure containing environment data.
 * @variable_name: The name of the environment variable to set or update.
 * @variable_value: The value to assign to the environment variable.
 *
 *  Return: 0 on success, 1 on failure.
 */
int set_or_update_environment_variable(info_t *info, char *variable_name, char *variable_value)
{
	char *environment_variable = NULL;
	list_t *node;
	char *ptr;

	if (!variable_name || !variable_value)
		return (0);

	environment_variable = malloc(string_strlen(variable_name) + string_strlen(variable_value) + 2);
	if (!environment_variable)
		return (1);
	string_cpy(environment_variable, variable_name);
	string_strcat(environment_variable, "=");
	string_strcat(environment_variable, variable_value);

	node = info->env;
	for (node = info->env; node; node = node->next)
	{
		ptr = string_starts_with(node->str, variable_name);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = environment_variable;
			info->environ_changed = 1;
			return (0);
		}
		node = node->next;
	}

	add_node_to_end_of_linked_list(&(info->env), environment_variable, 0);
	free(environment_variable);
	info->environ_changed = 1;

	return (0);
}

/**
 * remove_environment_variable - Unsets (removes) an environment variable from the process
 * environment.
 * @info: A pointer to a structure holding information about the
 * environment variables.
 * @var: The name of the environment variable to unset.
 *
 * This function searches for the specified environment variable within the
 * linked list of environment variables stored in the 'info' structure.
 * If found, it removes the variable from the environment by deleting the
 * corresponding node in the linked list.
 * The function also updates a flag in the 'info' structure to indicate
 * whether the environment has been changed.
 *
 * Return: If the specified variable is successfully unset,
 * returns a non-zero value to indicate that the environment has been changed.
 * Otherwise, returns 0.
 */
int remove_environment_variable(info_t *info, char *var)
{
	size_t index = 0;
	list_t *node;
	char *ptr;

	if (!info->env || !var)
		return (0);

	for (node = info->env; node; node = node->next, index++)
	{
		ptr = string_starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->environ_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
	}

	return (info->environ_changed);
}

#endif /* __EXECUTE_ENVIRONS__ */
