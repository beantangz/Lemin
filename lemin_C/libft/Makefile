# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 16:48:30 by mleineku          #+#    #+#              #
#    Updated: 2026/01/20 13:55:06 by mleineku         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

# Tous les .c sont maintenant dans functions/
SRCS = functions/ft_atoi.c \
       functions/ft_bzero.c \
       functions/ft_calloc.c \
       functions/ft_isalnum.c \
       functions/ft_isalpha.c \
       functions/ft_isascii.c \
       functions/ft_isdigit.c \
       functions/ft_isprint.c \
       functions/ft_memchr.c \
       functions/ft_memcmp.c \
       functions/ft_memcpy.c \
       functions/ft_memmove.c \
       functions/ft_memset.c \
       functions/ft_strchr.c \
       functions/ft_strdup.c \
       functions/ft_strjoin.c \
       functions/ft_strlcat.c \
       functions/ft_strlcpy.c \
       functions/ft_strncmp.c \
       functions/ft_strlen.c \
       functions/ft_strnstr.c \
       functions/ft_strrchr.c \
       functions/ft_strtrim.c \
       functions/ft_substr.c \
       functions/ft_tolower.c \
       functions/ft_toupper.c \
       functions/ft_split.c \
       functions/ft_itoa.c \
       functions/ft_strmapi.c \
       functions/ft_striteri.c \
       functions/ft_putstr_fd.c \
       functions/ft_putchar_fd.c \
       functions/ft_putendl_fd.c \
       functions/ft_putnbr_fd.c \
       functions/ft_printf.c \
       functions/printfunctions.c \
       functions/printfunctions2.c \
       functions/get_next_line_bonus.c \
       functions/get_next_line_utils_bonus.c

# Les fichiers objets seront dans le dossier obj
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC
AR = ar rcs
RM = rm -f
MKDIR = mkdir -p

# Default rule
all: $(NAME)

# Create .a library
$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

# Compile .o from .c into obj/
$(OBJ_DIR)/%.o: functions/%.c
	$(MKDIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean .o files
clean:
	$(RM) -rf $(OBJ_DIR)

# Clean .o files and .a
fclean: clean
	$(RM) $(NAME)

# Rebuild
re: fclean all