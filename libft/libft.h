/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shattori <shattori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:18:05 by shattori          #+#    #+#             */
/*   Updated: 2025/06/21 15:32:12 by shattori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "./ft_printf/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// for monolist
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

// for twinlist
typedef struct dnode
{
	int				data;
	struct dnode	*prev;
	struct dnode	*next;
}					t_DNode;

typedef struct dlist
{
	t_DNode			*head;
	t_DNode			*tail;
	int				size;
}					t_DList;
// for twinlist

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, unsigned int count);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strchr(const char *str, int c);
size_t				ft_strlcat(char *dest, const char *src, size_t len);
size_t				ft_strlen(const char *in);
size_t				ft_strlcpy(char *dest, const char *src, size_t len);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strrchr(const char *s, int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_calloc(size_t number, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlcat(char *dest, const char *src, size_t len);
int					ft_strncmp(const char *string1, const char *string2,
						size_t count);
char				*ft_substr(char const *s, unsigned int start, size_t z);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char *str, char *charset);
char				*ft_itoa(int n);
char				*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int					ft_putchar_fd(char c, int fd);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				add_back(t_DList *list, int data);
void				add_front(t_DList *list, int data);
t_DList				*create_dlist(void);
t_DNode				*create_node(int data);
void				free_list(t_DList *list);
char				**free_split(char **str);

#endif /* LIBFT_H */
