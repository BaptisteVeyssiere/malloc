##
## Makefile for malloc in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
## 
## Made by Baptiste Veyssiere
## Login   <veyssi_b@epitech.net>
## 
## Started on  Tue Jan 24 16:16:32 2017 Baptiste Veyssiere
##

NAME	= libmy_malloc.so

RM	= rm -f

CC	= gcc

MKDIR	= mkdir -p

SRC	= src/my_malloc.c \
	src/free.c \
	src/realloc.c \
	src/IntToHex.c

SRCDIR	= src

OBJDIR	= obj

OBJ	= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CFLAGS	= -W -Werror -Wextra -Wall

$(NAME): $(OBJ)
	@$(CC) -shared -o $(NAME) $(OBJ)
	@echo "Linking complete!"

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(MKDIR) $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -fpic
	@echo "Compiled "$<" successfully!"

all: $(NAME)

clean:
	@$(RM) $(OBJ)
	@echo "Cleanup complete!"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
