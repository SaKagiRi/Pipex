NAME 		= kml.a
FILE		= ft_atoi.c \
		ft_itoa.c \
		ft_bzero.c \
		ft_split.c \
		ft_strlen.c \
		ft_memset.c \
		ft_memcpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strchr.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c  \
		ft_strrchr.c \
		ft_memmove.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_striteri.c \
		ft_putstr_fd.c \
		ft_putnbr_fd.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_printf.c \
		gnl.c \
		argstr.c \
		fsplit.c \
		fjoin.c

CC 		= cc
AR_AND_FLAGS	= ar -rcs
RM		= rm -rf
CFLAGS		= -Wall -Wextra -Werror 
MKDIR		= mkdir -p
src_dir		= src
obj_dir		= obj
inc		= -I include
SRC		= $(addprefix $(src_dir)/, $(FILE))
OBJ		= $(addprefix $(obj_dir)/, $(FILE:%.c=%.o))
out_dir		= ./

all:		$(obj_dir) $(NAME) generate

coppy_header	:
			@cp include/kml.h $(out_dir)

$(obj_dir)/%.o:	$(src_dir)/%.c
			@$(CC) $(CFLAGS) $(inc) -c $< -o $@ && printf "Compiling: \033[0;32m$<\033[0m\n"

$(NAME):	 $(OBJ)
			@$(AR_AND_FLAGS) $(addprefix $(out_dir)/, $@) $^

$(obj_dir):
			@$(MKDIR) $(obj_dir)

clean:
	@$(RM) $(obj_dir) && printf "\033[1;31mDelete all Object file.\033[0m\n"

fclean:clean
	@$(RM) $(out_dir)/$(NAME) && printf "\033[1;31mRemove Libft.a file.\033[0m\n"

re:fclean all


.PHONY: all re clean fclean bonus generate start coppy_header


generate:
	@echo "\033[1;32m\n|-----------Generate all library complete.-----------|\033[0m\n"
