SRCS		=	src/main.cpp src/Server/create_http.cpp \
				src/Config/Config.cpp src/Logger/Logger.cpp src/Server/Server.cpp \
				src/ReturnStatus/ReturnStatus.cpp

OBJS		:= $(SRCS:.cpp=.o)
OBJS		:= $(addprefix obj/, $(OBJS))

CC 			= c++
RM			= rm -f
CFLAGS		= -std=c++98 #-Wall -Wextra -Werror 
NAME		= webserv
INCLUDE		= -Iinc/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

obj/%.o: %.cpp
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -rf obj/

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re