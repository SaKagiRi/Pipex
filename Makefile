NAME	= pipex
FILE	= pipex.c utils.c 
BFILE	= pipex_bonus.c utils_bonus.c ultils2_bonus.c
FLAGS	= -Wall -Wextra -Werror -g3 -o0 -fsanitize=address,undefined
CC	= cc
OBJD	= obj
SRCD	= src
INC	= include
KML	= KML

SRC	= $(addprefix $(SRCD)/, $(FILE))
OBJ	= $(addprefix $(OBJD)/, $(FILE:%.c=%.o))

BSRC	= $(addprefix $(SRCD)/, $(BFILE))

OUT	= ./

all:	$(OBJD) $(NAME)

$(OBJD)/%.o : $(SRCD)/%.c
	@$(CC) $(FLAGS) -I$(INC) -c $< -o $@

bonus: $(OBJD) $(BOBJ)
	@make -C $(KML) && $(CC) $(FLAGS) $(BSRC) $(KML)/kml.a -o $(OUT)/$(NAME)

$(NAME): $(OBJ) 
	@make -C $(KML) && $(CC) $(FLAGS) $(SRC) $(KML)/kml.a -I$(INC) -o $(OUT)/$(NAME)

$(OBJD):
	@mkdir -p $(OBJD)

clean:
	@rm -rf $(OBJD) && make clean -C $(KML)

fclean: clean
	@rm -rf $(OUT)/$(NAME) && make fclean -C $(KML)

re: fclean all

.PHONY: all clean fclean re bonus
