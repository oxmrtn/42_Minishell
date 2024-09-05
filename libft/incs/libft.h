/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:32:30 by mtrullar          #+#    #+#             */
/*   Updated: 2024/09/04 16:37:40 by mtrullar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ===== ENV LIST ===== */
typedef struct l_env
{
	void			*content;
	struct l_env	*next;
}					t_env;

t_env	*ft_envmap(t_env *lst, void *(*f)(void *), void (*del)(void *));
t_env	*ft_envnew(void *content);
t_env	*ft_envlast(t_env *lst);
void	ft_envadd_front(t_env **lst, t_env *new);
void	ft_envadd_back(t_env **lst, t_env *new);
void	ft_envdelone(t_env *lst, void (*del)(void *));
void	ft_envclear(t_env **lst, void (*del)(void *));
void	ft_enviter(t_env *lst, void (*f)(void *));
int		ft_envsize(t_env *lst);
/* ==================== */

void	ft_free_split(char **strs);
char	*ft_strjoin_c(char *s1, char *s2, char c, int sfree);
int		cpt_words(char *str, char c);

size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dest, char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

long	ft_atol(const char *nptr);

int		ft_max(int a, int b);
int		ft_atoi(const char *nptr);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_ultimate_len(char **str);
int		ft_memcmp(const void *pointer1, const void *pointer2, size_t size);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_tolower(int c);
int		ft_toupper(int c);

char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *src);
char	*ft_strdup_till_i(char *src, int i);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_s1(char *s1, char *s2);
char	*ft_strjoin_s2(char *s1, char *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int i, size_t len);

char	**ft_split(char *str, char c);

void	ft_print_tab(char **tab);
void	ft_freetab(char **tab);
void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nbr, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_puterror(char *str);

void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);

#endif