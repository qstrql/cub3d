# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjouot <mjouot@student.42angouleme.fr      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 15:48:29 by mjouot            #+#    #+#              #
#    Updated: 2023/06/13 11:10:13 by lbertaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAMEBONUS = cub3DBonus
SRCS = 	mandatory/SRCS/main.c \
		mandatory/SRCS/utils.c \
		mandatory/SRCS/debug.c \
		mandatory/SRCS/get_rgb.c \
		mandatory/SRCS/check_textures.c \
		mandatory/SRCS/check_map.c \
		mandatory/SRCS/check_map_utils.c \
		mandatory/SRCS/check_utils.c \
		mandatory/SRCS/init_utils.c \
		mandatory/SRCS/input_hook_setup.c \
		mandatory/SRCS/player_utils.c \
		mandatory/SRCS/parse_arg.c \
		mandatory/SRCS/parse_file.c \
		mandatory/SRCS/get_file_content.c \
		mandatory/SRCS/check_file_content_utils.c \
		mandatory/SRCS/init_structs.c \
		mandatory/SRCS/exit_program.c \
		mandatory/SRCS/free_data_struct.c \
		mandatory/SRCS/free_textures.c \
		mandatory/SRCS/get_next_line.c \
		mandatory/SRCS/cast_rays.c \
		mandatory/SRCS/draw_rays.c \
		mandatory/SRCS/rc_texture_utils.c

BONUSSRCS =	bonus/SRCS/main.c \
			bonus/SRCS/utils.c \
			bonus/SRCS/debug.c \
			bonus/SRCS/get_rgb.c \
			bonus/SRCS/check_textures.c \
			bonus/SRCS/check_map.c \
			bonus/SRCS/check_map_utils.c \
			bonus/SRCS/check_utils.c \
			bonus/SRCS/init_utils.c \
			bonus/SRCS/input_hook_setup.c \
			bonus/SRCS/display_to_screen.c \
			bonus/SRCS/player_utils.c \
			bonus/SRCS/parse_arg.c \
			bonus/SRCS/parse_file.c \
			bonus/SRCS/get_file_content.c \
			bonus/SRCS/check_file_content_utils.c \
			bonus/SRCS/init_structs.c \
			bonus/SRCS/exit_program.c \
			bonus/SRCS/free_data_struct.c \
			bonus/SRCS/free_textures.c \
			bonus/SRCS/get_next_line.c \
			bonus/SRCS/cast_rays.c \
			bonus/SRCS/draw_rays.c \
			bonus/SRCS/rc_texture_utils.c

CC = clang
FLAGS = -Wall -Werror -Wextra -I ./libft/INCLUDES/ -ggdb3
LIBMLX	:= MLX42
OBJS = $(SRCS:.c=.o)
BONUSOBJS=$(BONUSSRCS:.c=.o)

ifdef VAR
	SRCS = $(BONUSSRCS)
endif

all: libmlx $(NAME)

bonus: libmlx $(NAMEBONUS)

libmlx:
	if test -d $(LIBMLX)/build; then :; else cmake $(LIBMLX) -B $(LIBMLX)/build; fi
	make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(FLAGS) $^ -o $(NAME) libft/libft.a MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

$(NAMEBONUS): $(BONUSOBJS)
	make -C libft
	$(CC) $(FLAGS) $^ -o $(NAMEBONUS) libft/libft.a MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

%.o:%.c
	$(CC) $(FLAGS) -Imlx_linux -O3 -c $< -o $@

clean:
	make clean -C libft
	rm -f $(OBJS)
	rm -f $(BONUSOBJS)

fclean: clean
	if test -d $(LIBMLX)/build; then make clean -C $(LIBMLX)/build; else :; fi
	make fclean -C libft
	rm -f $(NAME)
	rm -f $(NAMEBONUS)

re: fclean all

.SILENT:
.PHONY: all clean fclean re bonus libmlx
#=============================================================================#
