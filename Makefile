# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 19:33:55 by diade-so          #+#    #+#              #
#    Updated: 2025/08/19 18:30:24 by diade-so         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
NAME = philo
LIB = libphilo.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -lpthread
INCLUDES = -I./includes

SRC_DIR = src
OBJ_DIR = obj
BONUS_DIR = bonus

# Source files
SRC_FILES = src/main.c \
	    src/utils.c \
	    src/init.c \
	    src/errors.c \
	    src/time.c \
	    src/cleanup.c


# Object files
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:.c=.o)))

# **************************************************************************** #
#                                   Rules                                      #
# **************************************************************************** #

all: $(NAME) $(LIB)

# Build executable from objects
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

# Build static lib without main.o so tests can provide main()
$(LIB): $(filter-out $(OBJ_DIR)/main.o, $(OBJ))
	ar rcs $(LIB) $^

# Compile rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/philo.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(LIB)

re: fclean all

.PHONY: all clean fclean re
