/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:01:07 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/19 12:18:14 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <stddef.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "struct.h"

# define NONE			0
# define PIPE			1
# define COMMAND		2
# define AND			3
# define OR				4
# define INPUT			5
# define HEREDOC		6
# define OUTPUT			7
# define APPEND			8
# define WHITESPACES " \t\n\v\r\f"
# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

t_list	*ft_init_env(char **env);
t_ast	*ft_init_ast(int ac, char **av);
char	*ft_getenv(char *key, t_list *lst_env);
char	*ft_getcwd(void);
char	*ft_subcdpath(char *cdpath); // to review
char	*solve_path(char *path, char *key);
char	*ft_three_strjoin(char *str1, char *str2, char *str3);
char	*ft_getenv_value(char *key, t_list *lst_env);
char	*ft_generate_prompt(t_list *lst_env, t_prompt *prompt);
char	**ft_convert_lst_to_tab(t_list *lst_env);
char	**arg_to_tab(t_arg *arg);
int		ft_pwd(int ac, char **av);
int		ft_exit(int ac, char **av, int status);
int		ft_env(t_list *env);
int		ft_export(int ac, char **av, t_list **env);
int		ft_unset(int ac, char **av, t_list **env);
int		ft_cd(int ac, char **av, t_list **env);
int		ft_echo(int ac, char **av);
int		ft_is_env_var(char *key, t_list *lst_env);
int		ft_have_env_var_home(t_list *env);
int		ft_get_end(void);
int		ft_exec_builtin(char **tab, t_list **lst_env);
int		ft_exec_redir(t_redir *redir);
int		ft_heredoc(int fd, char const *terminat);
int		ft_get_status(void);
int		is_redirect(char *str);
int		ft_is_builtin_fct(char *path);
int		tabsize(char **tab);
int		intern_init(t_prompt *prompt, char **env, t_list **lst_env);
int		ft_has_easy_syntax_error(char *line);
int		ft_easy_error_reviews(char *line);
int		ft_has_redir_before_pipe(char *line);
void	ft_cd_check_direct(t_cd *directory);
void	ft_cd_check_home_var(t_cd *directory);
void	ft_cd_check_beg_bslsh(t_cd *directory);
void	ft_cd_has_dots(t_cd *directory);
void	ft_cd_get_path(t_cd *directory);
void	ft_cd_dup_path(t_cd *directory);
void	ft_cd_set_path_to_arg(t_cd *directory);
void	ft_cd_clean_path(t_cd *directory);
void	ft_cd_check_len(t_cd *directory);
void	ft_cd_setenv(t_cd *directory);
void	ft_clean_saved_ast_link(void);
void	ft_save_ast_link(t_ast **ast);
void	print_ast(t_ast *ast, int level);
void	ft_clean_env_and_history(t_list **lst_env);
void	ft_clean_ast(t_ast **ast);
void	ft_execute_ast(t_ast *ast, t_list **lst_env, int *status);
void	ft_clean_prompt(int sig);
void	ft_handle_sigint_heredoc(int sig);
void	ft_pipe(t_ast *ast, t_list **lst_env, int *status);
void	ft_free_split(char ***tab);
void	ft_set_status(int status);
void	ft_setenv(char *key, char *value, t_list **lst_env);
void	ft_set_end(int status);
void	ft_minishell(t_prompt *prompt, t_list *lst_env);

#endif
