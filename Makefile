NAME		:= cub3d

CC			:= gcc

# CCFLAGS		:= -Wall -Wextra -Werror

HEADER_DIR	:= ./header/

INCLUDE		:=	$(foreach directory, $(HEADER_DIR), -I $(directory))

SRC_DIR		:= ./src/

SRC_FILE	:=	main.c mlx_utils.c

SRC			:=	$(foreach file, $(SRC_FILE), $(SRC_DIR)$(file))

all: $(NAME)

$(NAME): $(LIBFT) $(SRC)
	@$(CC) -g $(CCFLAGS) $(SRC) -o $@ $(INCLUDE) -lmlx -lXext -lX11 -lm
	@echo "\033[0;32mCub3d (>‿◠)\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -s
	@echo "\033[0;31mCub3d deleted (ㆆ_ㆆ)\033[0m"

clean:
	@make clean -s -C
	@rm -rf *.o

re: fclean all

$(OBJ_DIR):
	@mkdir -p $@

norma:
	@norminette ./

.PHONY: all fclean re