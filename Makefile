NAME = ircserv
FLAGS = -Wall -Wextra -Werror -std=c++98
SRC = *.cpp
INC = *.hpp
CC = c++

all: $(NAME)

$(NAME): $(SRC) $(INC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)
clean:
	@rm -f *.o
fclean: clean
	@rm -rf $(NAME)

re: fclean all