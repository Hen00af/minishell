/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nando <nando@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:40:32 by nando             #+#    #+#             */
/*   Updated: 2025/06/30 18:17:56 by nando            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_file_node	*get_files_in_cwd(void)
{
	DIR				*dir;
	struct dirent	*entry;
	t_file_node		*head;
	t_file_node		*tail;

	head = NULL;
	tail = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] == '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (!append_file_node(&head, &tail, entry->d_name))
		{
			free_file_list(head);
			closedir(dir);
			return (NULL);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (head);
}

t_file_node	*filter_matching_files(t_file_node *files, char *pattern)
{
	t_file_node	*head;
	t_file_node	*tail;

	head = NULL;
	tail = NULL;
	while (files)
	{
		if (is_match(pattern, files->name, 0, 0))
		{
			if (!append_file_node(&head, &tail, files->name))
				return (NULL);
		}
		files = files->next;
	}
	return (head);
}

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

char	*expand_wild_card(char *arg, t_expand *ctx)
{
	t_file_node	*files;
	t_file_node	*match_files;
	char		*joined;

	if (!has_wildcard(arg))
		return (ft_strdup(arg));
	files = get_files_in_cwd();
	match_files = filter_matching_files(files, arg);
	free_file_list(files);
	if (!match_files)
		return (ft_strdup(arg));
	if (match_files->next == NULL)
		return (match_files->name);
	ctx->wild_flag = 1;
	sort_files(match_files);
	joined = join_files(match_files);
	free_file_list(match_files);
	return (joined);
}
