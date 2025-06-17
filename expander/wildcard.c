/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:40:32 by nando             #+#    #+#             */
/*   Updated: 2025/06/17 09:32:16 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

typedef struct s_file_node
{
	char				*name;
	struct s_file_node	*next;
}						t_file_node;

bool	has_wildcard(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '*')
			return (true);
		i++;
	}
	return (false);
}

t_file_node	*create_new_node(char *file_name)
{
	t_file_node	*new_node;

	new_node = malloc(sizeof(t_file_node));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(file_name);
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_file_node	*get_files_in_cwd(void)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file_node		*head;
	t_file_node		*tail;
	t_file_node		*new_node;

	head = NULL;
	tail = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue ;
		new_node = create_new_node(entry->d_name);
		if (!new_node)
		{
			// freeで今までのリストを解放するべき。
			return (NULL);
		}
		if (!head)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
	}
	closedir(dir);
	return (head);
}

bool	is_match(const char *pattern, const char *str, int i, int j)
{
	if (pattern[i] == '\0' && str[j] == '\0')
		return (true);
	if (pattern[i] == '*')
	{
		return (is_match(pattern, str, i + 1, j) || (str[j] && is_match(pattern,
					str, i, j + 1)));
	}
	if (pattern[i] == str[j])
		return (is_match(pattern, str, i + 1, j + 1));
	return (false);
}

t_file_node	*filter_matching_files(t_file_node *files, char *pattern)
{
	t_file_node	*head;
	t_file_node	*tail;
	t_file_node	*new_node;

	head = NULL;
	tail = NULL;
	while (files)
	{
		if (is_match(pattern, files->name, 0, 0))
		{
			new_node = create_new_node(files->name);
			if (!new_node)
			{
				// freeで今までのリストを解放するべき。
				return (NULL);
			}
			if (!head)
			{
				head = new_node;
				tail = new_node;
			}
			else
			{
				tail->next = new_node;
				tail = new_node;
			}
		}
		files = files->next;
	}
	return (head);
}

void	swap_name(t_file_node *current, t_file_node *next)
{
	char	*tmp;

	tmp = current->name;
	current->name = next->name;
	next->name = tmp;
}

// bash同様に辞書順にソート(ノードの中身のみ入れ替え)
void	sort_files(t_file_node *head)
{
	t_file_node	*current;
	int			swap_flag;

	swap_flag = 1;
	while (swap_flag)
	{
		swap_flag = 0;
		current = head;
		while (current && current->next)
		{
			if (strcmp(current->name, current->next->name) > 0)
			{
				swap_name(current, current->next);
				swap_flag = 1;
			}
			current = current->next;
		}
	}
}

char	*join_files(t_file_node *head)
{
	char		*joined;
	char		*tmp;
	t_file_node	*current;

	joined = ft_strdup(head->name);
	current = head->next;
	while (current)
	{
		tmp = ft_strjoin(joined, " ");
		free(joined);
		joined = ft_strjoin(tmp, current->name);
		free(tmp);
		current = current->next;
	}
	return (joined);
}

// argには"echo *.c a*b" のようなnode->argv配列の各文字列（echo, *.c, a*b）が
//一つずつ入ってくる
char	*expand_wild_card(char *arg)
{
	t_file_node	*files;
	t_file_node	*match_files;
	char		*joined;

	if (has_wildcard(arg))
	{
		files = get_files_in_cwd();
		match_files = filter_matching_files(files, arg);
		if (!match_files)
			return (arg);
		sort_files(match_files);
		joined = join_files(match_files);
		return (joined);
	}
	return (arg);
}

// void	test_expand(char *pattern)
//{
//	char	*result;

//	result = expand_wild_card(pattern);
//	printf("Pattern: %-15s → Expanded: %s\n", pattern, result);
//	if (result != pattern)
//		free(result); // argと同じならfree不要
//}

// int	main(void)
//{
//	printf("==== Wildcard Pattern Expansion Test ====\n");
//	test_expand("*");
//	test_expand("*.c");
//	test_expand("*.h");
//	test_expand("*.txt");
//	test_expand("a*");
//	test_expand("*z*");
//	test_expand("abc*");
//	test_expand("ab*123*");
//	test_expand("main.c");
//	test_expand("no_match*");
//	return (0);
//}