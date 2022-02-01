# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acretu <acretu@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/15 16:38:35 by acretu            #+#    #+#              #
#    Updated: 2022/01/15 18:55:38 by acretu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= 	gcc
CFLAGS	= 	-Wall -Wextra -Werror

AR		= 	ar -rcsv
RM		= 	rm -f

NAME	= 	pipex


STD		= 	srcs/pipex.c \
			srcs/error_utils.c \
			srcs/ft_check_path.c \
			srcs/libft_utils.c\
			srcs/libft_utils2.c \
			srcs/pipex_utils.c
			
BON 	=	srcs/pipex_bonus.c \
			srcs/error_utils.c \
			srcs/ft_check_path.c \
			srcs/libft_utils.c\
			srcs/libft_utils2.c \
			srcs/pipex_utils.c\
			srcs/get_next_line.c \
			srcs/libft_utils_bonus.c \
			srcs/pipex_utils_bonus2.c 
			
OBJ		= 	${STD:.c=.o}
BON_OBJ	=	${BON:.c=.o}
			

all:		$(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

bonus:		$(BON_OBJ)
			@$(CC) $(CFLAGS) -o $(NAME) $(BON_OBJ)

clean: 
			$(RM) $(OBJ) $(BON_OBJ)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re bonus