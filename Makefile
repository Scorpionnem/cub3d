NAME := cub3D
SOURCE_DIR := ./src/
OBJ_DIR := ./obj/
INCLUDE_DIRS := ./includes/ ./libs/libft ./libs/gnl ./MLX42/include/MLX42
INCLUDE_DIRS := $(addprefix -I, $(INCLUDE_DIRS))

MAKE := @make --no-print-directory
MAKE_LIBFT := $(MAKE) -C libs/libft
MAKE_GNL := $(MAKE) -C libs/gnl
LIBFT := libs/libft/libft.a
GNL := libs/gnl/gnl.a
MLX := MLX42/build/libmlx42.a

SOURCE_DIR := ./src/
OBJ_DIR := ./obj/

OBJECTS = $(SOURCES:.c=.o)

C_FILES := main ctx error textures \
			parsing/read_file parsing/parse_map parsing/parse_file parsing/parse_file_internals parsing/parse_sprites \
			parsing/parse_utils \
			utils/string_manip utils/ft_safe_atoi utils/color_manip utils/time_manip \
			game/hooks game/render game/movement game/render_utils/draw_line game/render_utils/pixels_manip game/render_walls \
			game/render_utils/math_utils game/wall_utils/horizontal_rays game/wall_utils/vertical_rays \
			game/mouse game/render_walls_internals game/render_utils/fps game/doors \
			game/sprite game/sprite_internals game/sprite_utils game/minimap_draw game/render_minimap game/minimap_conflict \

C_FILES := $(addsuffix .c, $(C_FILES))

SOURCES := $(addprefix $(SOURCE_DIR), $(C_FILES))

OBJECTS := $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

#FLAGS
CFLAGS = -Wall -Werror -Wextra -g
MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm

all: mlx $(NAME)

mlx :
	@if ls | grep -q "MLX42"; then \
		echo "\033[0;32mMLX42 already exists ✅\033[0m"; \
	else \
		git clone https://github.com/codam-coding-college/MLX42.git; \
		cmake ./MLX42 -B ./MLX42/build; \
		make -C ./MLX42/build --no-print-directory -j4; \
		make --directory ./MLX42/build; \
	fi


$(OBJECTS): $(OBJ_DIR)%.o : $(SOURCE_DIR)%.c
	@cc $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(OBJ_DIR):
	@(cd $(SOURCE_DIR) && find . -type d -exec mkdir -p -- $(shell pwd)/$(OBJ_DIR){} \;)

$(NAME): $(OBJ_DIR) $(LIBFT) $(GNL) $(OBJECTS)
	@cc $(OBJECTS) $(LIBFT) $(GNL) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "$(NAME) compiled"

bonus: $(NAME)

$(LIBFT):
	$(MAKE_LIBFT)

$(GNL):
	$(MAKE_GNL)

display_clean_message := 1

clean:
	$(MAKE_LIBFT) clean
	$(MAKE_GNL) clean
	@rm -rf $(OBJ_DIR)
	@if [ $(display_clean_message) -eq 1 ] ;\
	then \
		echo "Clean done" ;\
	fi

fclean:
	$(MAKE_LIBFT) fclean
	$(MAKE_GNL) fclean
	$(MAKE) display_clean_message=0 clean
	@rm -f $(NAME)
	@echo "Fclean done"

re: fclean all

.PHONY: all clean fclean re bonus