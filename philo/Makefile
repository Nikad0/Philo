#######################################
#########      NAME      ##############
#######################################

NAME = philo

#######################################
######### FLAGS & COMPIL ##############
#######################################

CC = cc 
CFLAGS = -Wall -Wextra -Werror -g3 
MAKEFLAGS += --no-print-directory
SANITIZE = -fsanitize=thread -pthread
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes
HELGRIND = valgrind --tool=helgrind

#######################################
######### FILES / HEADERS #############
#######################################

SOURCES = 	srcs/main.c     		  \
			srcs/utils.c	          \
			srcs/inits.c              \
			srcs/routine.c            \
			srcs/monitoring.c         \
			srcs/mutex_utils.c        \
			srcs/exit_philo.c         \
			srcs/fork.c               \

#######################################
#########      BUILD     ##############
#######################################

SRC_DIR = srcs/
BUILD_DIR = .build/
DEPS := $(OBJS:.o=.d)
INCS = -I ./include -I .

OBJS = $(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SOURCES))
DEPS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.d,$(SRCS))

#######################################
#########      RULES     ##############
#######################################

all: $(NAME)

$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) -pthread $(OBJS) $(INCS) -o $@
	@echo "\n✅ $(NAME) compiled successfully!✅"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c Makefile include/philo.h | $(BUILD_DIR)
	@echo "\t Compiling $<"
	@$(CC) $(CFLAGS) $(INCS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	@mkdir -p $@
	@echo "🛠️  Building $(NAME)...\n"

#######################################
#########      CLEAN     ##############
#######################################

clean:
	@$(RM) -rf $(BUILD_DIR)
	@#$(MAKE) -s -C libft fclean
	@echo " Object files cleaned"
	@echo " Object files removed"
	@echo "\n\t ✅ clean successfull ! ✅\n"


fclean: clean
	@$(RM) $(NAME)
	@echo " Executable removed"
	@echo "\n\t ✅ fclean successfull ! ✅"

re: 
	@$(MAKE) -s fclean
	@$(MAKE) -s all


#######################################
#########      DEBUG     ##############
#######################################

valgrind: $(NAME)
	@echo "\n\t ⚠️  runing valgrind program !  ⚠️  \n"
	@read -p "Enter args: " args; \
	$(VALGRIND) ./$(NAME) -pthread $$args

helgrind: $(NAME)
	@echo "\n\t ⚠️  runing valgrind program !  ⚠️  \n"
	@read -p "Enter args: " args; \
	$(HELGRIND) ./$(NAME) -pthread $$args

sanitize: fclean
	@$(CC) $(CFLAGS) -pthread $(SANITIZE_FLAGS) $(SOURCES) $(INCS) -o $(NAME)
	@echo "\n\t ⚠️  runing sanitize program !  ⚠️  \n"
	@read -p "Enter args: " args; \
	./$(NAME) $$args

#######################################
#########      HELP      ##############
#######################################

help:
	@echo "Available targets:\n"
	@echo "\t all      - Build $(NAME) (default)"
	@echo "\t clean    - Remove object files"
	@echo "\t fclean   - Remove object files and executable"  
	@echo "\t re       - Clean and rebuild"
	@echo "\t valgrind - Run with : valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes"
	@echo "\t helgrind - run with : valgrind --tool=helgrind --trace-children=yes --track-fds=yes"
	@echo "\t sanitize - run with : -g3 -fsanitize=thread -pthread"
	@echo "\t help     - Show this help\n"

.PHONY: all clean fclean re FORCE libft run valgrind sanitize help