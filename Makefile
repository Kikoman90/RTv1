# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsidler <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/09 13:47:47 by fsidler           #+#    #+#              #
#    Updated: 2016/08/24 17:27:55 by fsidler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RTv1
CC = clang
LIB_NAME = ft
LIBDIR = libft
FLAGS = -Wall -Wextra -Werror

HEADERS = includes

SOURCES = srcs/add.c \
		  srcs/key.c \
		  srcs/add2.c \
		  srcs/draw.c \
		  srcs/free.c \
		  srcs/main.c \
		  srcs/inter.c \
		  srcs/mouse.c \
		  srcs/parser.c \
		  srcs/objects.c \
		  srcs/lighting.c \

OBJECTS = $(SOURCES:.c=.o)

$(NAME): $(LIBDIR)/lib$(LIB_NAME).a $(OBJECTS)
	@$(CC) $(FLAGS) -L $(LIBDIR) -l $(LIB_NAME) -o $@ $^ -lmlx -framework OpenGL -framework AppKit -lpthread
	@echo "compiling [ $(NAME) ] SUCCESS"

$(LIBDIR)/lib$(LIB_NAME).a : 
	@$(MAKE) -C $(LIBDIR)

all: $(NAME)

%.o: %.c $(HEADERS)/rtv1.h
	@$(CC) $(FLAGS) -I $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)
	@make clean -C $(LIBDIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBDIR)

re: fclean $(NAME)

.PHONY: all, clean, fclean, re
