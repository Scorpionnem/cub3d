NAME := cub3D
NAME_BONUS := cub3D_bonus

OBJ_DIR := ./obj/
INCLUDE_DIRS := ./includes/ ./libs/libft ./libs/gnl ./MLX42/include/MLX42
INCLUDE_DIRS_BONUS := ./includes_bonus/ ./libs/libft ./libs/gnl ./MLX42/include/MLX42

INCLUDE_DIRS := $(addprefix -I, $(INCLUDE_DIRS))
INCLUDE_DIRS_BONUS := $(addprefix -I, $(INCLUDE_DIRS_BONUS))

MAKE := @make --no-print-directory
MAKE_LIBFT := $(MAKE) -C libs/libft
MAKE_GNL := $(MAKE) -C libs/gnl
LIBFT := libs/libft/libft.a
GNL := libs/gnl/gnl.a
MLX := MLX42/build/libmlx42.a

SOURCE_DIR := ./src/
SOURCE_DIR_BONUS := ./src_bonus/

OBJ_DIR := ./obj/
OBJ_DIR_BONUS := ./obj_bonus/

OBJECTS = $(SOURCES:.c=.o)

C_FILES := main ctx error textures \
			parsing/read_file parsing/parse_map parsing/parse_file parsing/parse_file_internals \
			parsing/parse_utils \
			utils/string_manip utils/ft_safe_atoi utils/color_manip utils/time_manip \
			game/hooks game/render game/movement game/render_utils/draw_line game/render_utils/pixels_manip game/render_walls \
			game/render_utils/math_utils game/wall_utils/horizontal_rays game/wall_utils/vertical_rays \
			game/mouse game/render_walls_internals game/render_utils/fps game/doors \
			game/render_minimap game/minimap_draw \

C_FILES_BONUS := main ctx error textures \
			parsing/read_file parsing/parse_map parsing/parse_file parsing/parse_file_internals parsing/parse_sprites \
			parsing/parse_utils \
			utils/string_manip utils/ft_safe_atoi utils/color_manip utils/time_manip \
			game/hooks game/render game/movement game/render_utils/draw_line game/render_utils/pixels_manip game/render_walls \
			game/render_utils/math_utils game/wall_utils/horizontal_rays game/wall_utils/vertical_rays \
			game/mouse game/render_walls_internals game/render_utils/fps game/doors \
			game/sprite game/sprite_internals game/sprite_utils game/render_minimap game/minimap_draw \

C_FILES := $(addsuffix .c, $(C_FILES))

C_FILES_BONUS := $(addsuffix .c, $(C_FILES_BONUS))

SOURCES := $(addprefix $(SOURCE_DIR), $(C_FILES))

SOURCES_BONUS := $(addprefix $(SOURCE_DIR_BONUS), $(C_FILES_BONUS))

OBJECTS := $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

OBJECTS_BONUS := $(addprefix $(OBJ_DIR_BONUS), $(C_FILES_BONUS:.c=.o))

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

$(OBJECTS_BONUS): $(OBJ_DIR_BONUS)%.o : $(SOURCE_DIR_BONUS)%.c
	@cc $(CFLAGS) $(INCLUDE_DIRS_BONUS) -c $< -o $@

$(OBJ_DIR):
	@(cd $(SOURCE_DIR) && find . -type d -exec mkdir -p -- $(shell pwd)/$(OBJ_DIR){} \;)

$(OBJ_DIR_BONUS):
	@(cd $(SOURCE_DIR_BONUS) && find . -type d -exec mkdir -p -- $(shell pwd)/$(OBJ_DIR_BONUS){} \;)

$(NAME): $(OBJ_DIR) $(LIBFT) $(GNL) $(OBJECTS)
	@cc $(OBJECTS) $(LIBFT) $(GNL) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "\033[0;32mCompiled $(NAME) ✅\033[0m"

$(NAME_BONUS): $(OBJ_DIR_BONUS) $(LIBFT) $(GNL) $(OBJECTS_BONUS)
	@cc $(OBJECTS_BONUS) $(LIBFT) $(GNL) $(MLX) $(MLXFLAGS) -o $(NAME_BONUS)
	@echo "\033[0;32mCompiled $(NAME_BONUS) ✅\033[0m"

bonus: mlx $(NAME_BONUS)

$(LIBFT):
	$(MAKE_LIBFT)

$(GNL):
	$(MAKE_GNL)

clean:
	$(MAKE_LIBFT) clean
	$(MAKE_GNL) clean
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_BONUS)
	@echo "\033[0;32mCleaned objects ✅\033[0m"

fclean:
	$(MAKE_LIBFT) fclean
	$(MAKE_GNL) fclean
	$(MAKE) clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@echo "\033[0;32mCleaned everything ✅\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus