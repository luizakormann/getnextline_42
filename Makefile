# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luiza <luiza@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/02 12:22:29 by luiza             #+#    #+#              #
#    Updated: 2025/02/17 10:53:00 by luiza            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               configuration                                  #
# **************************************************************************** #

CC	= cc
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -rf
NAME	= $(BIN_DIR)gnl.a
TEST_EXEC	= $(BIN_DIR)gnl_exec

# **************************************************************************** #
#                                    paths                                     #
# **************************************************************************** #

OBJ_DIR	= obj/
SRC_DIR = src/
BIN_DIR = bin/
INC_DIR = include/

# **************************************************************************** #
#                                   files                                      #
# **************************************************************************** #

SRC_FILES	= $(addprefix $(SRC_DIR), get_next_line.c utils.c build_fts.c\
	read_fts.c struct_fts.c)
EXEC_FILES	= $(addprefix $(SRC_DIR), get_next_line.c utils.c build_fts.c\
	read_fts.c .c main.c)
OBJS_FILES	= $(notdir $(SRC_FILES:.c=.o))

# **************************************************************************** #
#                              compile commands                                #
# **************************************************************************** #

AR	:= ar -rcs
COMPILE_FILES	= $(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $(OBJ_DIR)$@
CREATE_LIB	= $(AR) $(NAME) $(addprefix $(OBJ_DIR), $(OBJS_FILES))

# **************************************************************************** #
#                                  targets                                     #
# **************************************************************************** #

all: $(NAME)

%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(COMPILE_FILES)

$(NAME): $(OBJS_FILES)
	mkdir -p $(BIN_DIR)
	$(CREATE_LIB)

$(TEST_EXEC): $(OBJS_FILES) main.o
	$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR), $(OBJS_FILES) main.o) -o $(TEST_EXEC)


clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(BIN_DIR)

re: fclean all

test: $(TEST_EXEC)

.PHONY: all clean fclean re test
