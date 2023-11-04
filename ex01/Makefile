SRCS =	$(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.o)

NAME =  RPN

CC = c++

FLAGS =   -Werror -Wall -Wextra -std=c++98

#Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m
ORANGE		=	\e[38;5;208m
PURPLE		=	\e[38;5;129m
PINK 		= 	\e[38;2;255;192;203m
RED         =   \E[31m
all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@printf "$(GREEN)    - Executable ready.\n$(RESET)"
	@printf "${PURPLE}     Reverse \n $(RESET)\n"
	@printf "${WHITE} ######################\n$(RESET)"
	@printf "${WHITE} ######################\n$(RESET)"
	@printf "${WHITE} ######################\n$(RESET)"
	@printf "${WHITE} ######################\n$(RESET)"
	@printf "${WHITE} ######################\n$(RESET)"
	@printf "${WHITE} ######################\n$(RESET)"
	@printf "${RED} ######################\n$(RESET)"
	@printf "${RED} ######################\n$(RESET)"
	@printf "${RED} ######################\n$(RESET)"
	@printf "${RED} ######################\n$(RESET)"
	@printf "${RED} ######################\n$(RESET)"

	@printf "${PURPLE} Notation \n $(RESET)"



%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re