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
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes

#######################################
######### FILES / HEADERS #############
#######################################

SOURCES = 	srcs/main.c                \

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

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(INCS) $(LIBFT) -o $@
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
	@$(MAKE) -s -C libft fclean
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
	@echo "\n\t ⚠️  runing program !  ⚠️  \n"
	$(VALGRIND) ./$(NAME)

#######################################
#########      HELP      ##############
#######################################

help:
	@echo "Available targets:\n"
	@echo "\t all      - Build $(NAME) (default)"
	@echo "\t clean    - Remove object files"
	@echo "\t fclean   - Remove object files and executable"  
	@echo "\t re       - Clean and rebuild"
	@echo "\t valgrind - Run with valgrind"
	@echo "\t help     - Show this help\n"

.PHONY: all clean fclean re FORCE libft run valgrind help