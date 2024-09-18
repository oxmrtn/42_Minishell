# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtrullar <mtrullar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 20:58:55 by mtrullar          #+#    #+#              #
#    Updated: 2024/09/18 11:03:29 by mtrullar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

NAME		=	libcustomft.a
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g3

#Folders
INCLUDE		=	incs/
LIBFT 		=	libft/
PRINTF 		=	ft_printf/
GNL 		=	gnl/

OBJ_DIR		=	obj/

RM			=	@rm -rf

#Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

BOLD = \e[1m
RESET = \e[0m

RESET_LINE			=	\033[A\033[K

LIBFTSRC = 	ft_atoi.c	 			\
			ft_freetab.c			\
			ft_bzero.c 				\
			ft_isalnum.c 			\
			ft_isalpha.c 			\
			ft_isascii.c 			\
			ft_isdigit.c 			\
			ft_isprint.c 			\
			ft_memchr.c 			\
			ft_memcmp.c 			\
			ft_memcpy.c 			\
			ft_memmove.c 			\
			ft_memset.c 			\
			ft_strchr.c 			\
			ft_strlcat.c 			\
			ft_strlcpy.c 			\
			ft_strlen.c 			\
			ft_strncmp.c 			\
			ft_strnstr.c 			\
			ft_strrchr.c 			\
			ft_tolower.c 			\
			ft_toupper.c 			\
			ft_calloc.c 			\
			ft_strdup.c 			\
			ft_substr.c 			\
			ft_strjoin.c 			\
			ft_strtrim.c 			\
			ft_split.c 				\
			ft_split_quote.c		\
			ft_itoa.c 				\
			ft_strmapi.c 			\
			ft_striteri.c 			\
			ft_putchar_fd.c			\
			ft_putstr_fd.c 			\
			ft_putendl_fd.c 		\
			ft_putnbr_fd.c			\
			ft_lstnew.c 			\
			ft_lstadd_front.c 		\
			ft_lstsize.c 			\
			ft_lstlast.c 			\
			ft_lstadd_back.c 		\
			ft_lstdelone.c 			\
			ft_lstclear.c 			\
			ft_lstiter.c 			\
			ft_lstmap.c				\
			ft_ultimate_len.c		\
			ft_max.c				\

PRINTFSRC = ft_print_pointer.c		\
			ft_printf.c				\
			ft_putfunc.c			\
			ft_putnbr_unsigned.c	\
			ft_putnbrbase.c			\

GNLSRC	  = get_next_line_bonus.c		\
			get_next_line_utils_bonus.c	\

# LIBFT
SRC_LIBFT	= 	$(addprefix $(LIBFT), $(LIBFTSRC))
OBJ_LIBFT	= 	$(addprefix $(OBJ_DIR), $(LIBFTSRC:.c=.o))
# PRINTF
SRC_PRINTF	=	$(addprefix $(PRINTF), $(PRINTFSRC))
OBJ_PRINTF	= 	$(addprefix $(OBJ_DIR), $(PRINTFSRC:.c=.o))
# GET_NEXT_LINE
SRC_GNL		=	$(addprefix $(GNL), $(GNLSRC))
OBJ_GNL		= 	$(addprefix $(OBJ_DIR), $(GNLSRC:.c=.o))

OBJF		=	.cache_exists

all: $(NAME)

$(NAME):$(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL)
	@ar rc $(NAME) $(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL)
	@ranlib $(NAME)
	@echo "$(RESET_LINE)$(BLUE)$(BOLD)[ CUSTOMFT ]$(RESET)$(DEF_COLOR)	COMPILED $(GREEN) ✔ $(DEF_COLOR)\n"

	
$(OBJ_DIR)%.o: $(LIBFT)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	@echo "$(RESET_LINE)$(BLUE)$(BOLD)[ LIBFT ]$(RESET)$(DEF_COLOR)	compiling: $< $(GREEN) ✔ $(DEF_COLOR)"

$(OBJ_DIR)%.o: $(PRINTF)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	@echo "$(RESET_LINE)$(BLUE)$(BOLD)[ GNL   ]$(RESET)$(DEF_COLOR)	compiling: $< $(GREEN) ✔ $(DEF_COLOR)"

$(OBJ_DIR)%.o: $(GNL)%.c | $(OBJF)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	@echo "$(RESET_LINE)$(BLUE)$(BOLD)[ PRINTF ]$(RESET)$(DEF_COLOR)	compiling: $< $(GREEN) ✔ $(DEF_COLOR)"

$(OBJF):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL) $(OBJ_DIR)
	@echo "$(BLUE)Libft obj cleaned$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RESET_LINE)$(CYAN)Libft fcleaned !$(DEF_COLOR)"

re: fclean all
	@echo "$(GREEN)\e[1mEverything has been rebuilt, fresh and clean\e[0m$(DEF_COLOR)"

.PHONY: all clean fclean re