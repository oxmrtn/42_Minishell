/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:32:30 by mtrullar          #+#    #+#             */
/*   Updated: 2024/10/17 14:14:54 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct l_list
{
	void			*content;
	struct l_list	*next;
}					t_list;

typedef struct s_nk
{
	int		i;
	int		j;
	int		k;
	int		m;
	int		check;
	char	*buffer;
}			t_nk;

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
int			ft_lstsize(t_list *lst);

int			ft_iswhite(char *str);
int			ft_ultimate_compare(char *s1, char *s2);
void		ft_free_split(char **strs);
char		*ft_strjoin_c(char *s1, char *s2, char c, int sfree);
int			cpt_words(char *str, char c);

size_t		ft_strlen(const char *str);
size_t		ft_custom_len(char *src);
size_t		ft_strlcat(char *dest, char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

long		ft_atol(const char *nptr);

long long	ft_atoll(const char *nptr);

int			ft_max(int a, int b);
int			ft_atoi(const char *nptr);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_iqt(int c);
int			ft_strisdigit(char *str);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_ultimate_len(char **str);
int			ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
int			ft_ultimate_compare(char *s1, char *s2);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_count_char_behind(char *str, int i, char c);

char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(char *src);
char		*ft_strdup_till_i(char *src, int i);
char		*ft_strdup_custom(char *src);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin_s1(char *s1, char *s2);
char		*ft_strjoin_s2(char *s1, char *s2);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int i, size_t len);

char		**ft_split(char *str, char c);
char		**ft_split_quote(char const *s, char c);

void		ft_print_tab(char **tab);
void		ft_freetab(char **tab);
void		ft_bzero(void *s, size_t n);
void		ft_putchar_fd(char c, int fd);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int nbr, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_puterror(char *str);
void		ft_desc_error(char *cmd, char *wrong, int order, char *err);

void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);

#endif
