
#include "../../includes/minishell.h"

t_cmd_list	*create_node(char *tkn, int tkn_value)
{
	t_cmd_list	*new;

	new = malloc(sizeof(t_cmd_list));
	if (!new)
		return (NULL); // protect better, exit?
	new->elem = strdup(tkn);
	new->pipe = FALSE;
	new->cmd = FALSE;
	new->builtin = FALSE;
	new->arg = FALSE;
	if (tkn_value == PIPE)
		new->pipe = TRUE;
	else if (tkn_value == CMD)
		new->cmd = TRUE;
	// if (tkn_value == BUILTIN)
		// new->builtin = TRUE;
	else if (tkn_value == ARG)
		new->arg = TRUE;
	new->next = NULL;
	return (new);
}

void	link_new_node(t_cmd_list **lst, t_cmd_list *new)
{
	t_cmd_list	*temp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

t_cmd_list	*set_cmd_list(char **tkn, int *tkn_value)
{
	t_cmd_list	*cmd;
	t_cmd_list	*new_node;
	int		i;

	i = -1;
	cmd = NULL;
	while (tkn[++i])
	{
		new_node = create_node(tkn[i], tkn_value[i]);
		link_new_node(&cmd, new_node);
	}
	return (cmd);
}
