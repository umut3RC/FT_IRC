CC = c++
CPPFLAG = -Wall -Wextra -Werror -std=c++98
NAME = ircserv
SRC = srcs/*.cpp srcs/commands/*.cpp
HEADERS = include/*.hpp

all: $(NAME)

$(NAME): $(SRC) $(HEADERS)
	@$(CC) $(CPPFLAG) $(SRC) -o $(NAME)
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean $(NAME)

.PHONY:all re clean fclean
