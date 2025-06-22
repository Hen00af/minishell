#include "./parser.h"

t_ast	*parse_pipeline(t_token **cur)
{
	t_ast	*left;
	t_ast	*right;

	left = parse_command_or_subshell(cur);
	if (!left)
		return (NULL);
	while (*cur && (*cur)->type == TOK_PIPE)
	{
		*cur = (*cur)->next;
		right = parse_command_or_subshell(cur);
		if (!right)
		{
			ft_fprintf(STDERROR_INT, "Syntax error after pipe\n");
			return (NULL);
		}
		left = create_ast_node(NODE_PIPE, left, right);
	}
	return (left);
}

t_ast	*parse_subshell(t_token **cur)
{
	t_ast	*inner;
	t_ast	*node;

	if (!*cur || (*cur)->type != TOK_LPAREN)
		return (NULL);
	*cur = (*cur)->next;
	inner = parse_and_or(cur);
	if (!inner)
		return (NULL);
	if (!*cur || (*cur)->type != TOK_RPAREN)
		return (NULL);
	*cur = (*cur)->next;
	node = calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	node->left = inner;
	return (node);
}
t_ast	*parse_command_or_subshell(t_token **cur)
{
	if ((*cur)->type == TOK_LPAREN)
		return (parse_subshell(cur));
	return (parse_command(cur));
}
