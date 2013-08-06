
NAME = 				test_json

CXXFLAGS += 	-Wall -Wextra -Werror
CXXFLAGS += 	-I ../

ifeq ($(VERBOSE), true)

CXXFLAGS +=		-D VERBOSE

endif

ECHO = 				echo

OBJS = 				test.o

all: 					$(NAME)

run:					$(NAME)
							@./$(NAME)

$(NAME): 			$(OBJS)
							$(CXX) $(OBJS) -o $(NAME)
							@$(ECHO) Compilation done

clean:
							@$(ECHO) Remove compiled files
							@$(RM) $(OBJS)

fclean: 			clean
							@$(ECHO) Remove $(NAME)
							@$(RM) $(NAME)

re:						fclean all

.PHONY: 			all clean fclean re