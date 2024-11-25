# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 16:12:33 by lukorman          #+#    #+#              #
#    Updated: 2024/11/25 17:08:30 by lukorman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               configuration                                  #
# **************************************************************************** #

CC	= cc
BUFFER_SIZE ?= 64
CFLAGS	= -Wall -Wextra -Werror -d BUFFER_SIZE=$(BUFFER_SIZE)
RM	= rm -rf
NAME	= get_next_line.a

# **************************************************************************** #
#                                   files                                      #
# **************************************************************************** #

SRC_FILES	= get_next_line.c get_next_line_utils.c
#SRC_BONUS	=
OBJS_FILES	= $(SRC_FILES:.c=.o)
#OBJS_BONUS	= $(SRC_BONUS:.c=.o)
#ALL_OBJS	= $(OBJS_FILES) $(OBJS_BONUS)

# **************************************************************************** #
#                              compile commands                                #
# **************************************************************************** #

AR	:= ar -rcs
COMPILE_OBJS	= $(CC) $(CFLAGS) -c $< -o $@
COMPILE_LIB_FILES	= $(AR) $(NAME) $(OBJS_FILES)
#COMPILE_LIB_BONUS	= $(AR) $(NAME) $(ALL_OBJS)

# **************************************************************************** #
#                                 check relink                                 #
# **************************************************************************** #

#ifeq ($(findstring bonus,$(MAKECMDGOALS)),bonus)
#	OBJS += $(OBJS_BONUS)
#endif

# **************************************************************************** #
#                                  targets                                     #
# **************************************************************************** #

all: $(NAME)

%.o: %.c
	$(COMPILE_OBJS)

$(NAME): $(OBJS_FILES)
	$(COMPILE_LIB_FILES)

#bonus: $(ALL_OBJS)
#	$(COMPILE_LIB_BONUS)

clean:
	$(RM) $(COMPILE_LIB_FILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
