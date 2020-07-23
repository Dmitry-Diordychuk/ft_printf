# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdustin <kdustin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/24 15:33:18 by kdustin           #+#    #+#              #
#    Updated: 2020/07/23 02:17:08 by kdustin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LIBFT_DIR = libft/
LIBFT_A = libft.a

INC_DIR = includes/
SRC_DIR = sources/

INC_FILES =	$(addprefix $(INC_DIR),ft_printf.h)
OBJ_FILES =	ft_printf.o		\
			fsm_utils.o		\
			fsm_init.o		\
			format.o		\
			print_c.o		\
			print_s.o		\
			print_p.o		\
			print_x.o		\
			print_id.o		\
			print_u.o		\
			print_utils.o	\
			validate.o

CFLAGS = -Werror -Wextra -Wall

all: $(NAME)

$(NAME): $(OBJ_FILES)
	make bonus -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)$(LIBFT_A) $(NAME)
	ar rc $@ $^
	ranlib $(NAME)

%.o: $(SRC_DIR)%.c $(INC_FILES)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $<

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJ_FILES)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: fclean re all clean
