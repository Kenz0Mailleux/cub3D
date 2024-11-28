NAME = libfinal.a

MODULE1_DIR = original
MODULE2_DIR = printf
MODULE3_DIR = gnl

MODULE1_LIB = $(MODULE1_DIR)/libft.a
MODULE2_LIB = $(MODULE2_DIR)/libftprintf.a
MODULE3_LIB = $(MODULE3_DIR)/lbftgnl.a

LIBS = $(MODULE1_LIB) $(MODULE2_LIB) $(MODULE3_LIB)

all: $(NAME)

$(NAME): $(LIBS)
	@ar rcs $(NAME) $(LIBS) > /dev/null 2>&1
	@echo "Final library created: $(NAME)"

$(MODULE1_LIB):
	@$(MAKE) -C $(MODULE1_DIR) > /dev/null 2>&1

$(MODULE2_LIB):
	@$(MAKE) -C $(MODULE2_DIR) > /dev/null 2>&1

$(MODULE3_LIB):
	@$(MAKE) -C $(MODULE3_DIR) > /dev/null 2>&1

clean:
	@$(MAKE) -C $(MODULE1_DIR) clean > /dev/null 2>&1
	@$(MAKE) -C $(MODULE2_DIR) clean > /dev/null 2>&1
	@$(MAKE) -C $(MODULE3_DIR) clean > /dev/null 2>&1
	@echo "Cleaned object files from all modules"

fclean: clean
	@$(MAKE) -C $(MODULE1_DIR) fclean > /dev/null 2>&1
	@$(MAKE) -C $(MODULE2_DIR) fclean > /dev/null 2>&1
	@$(MAKE) -C $(MODULE3_DIR) fclean > /dev/null 2>&1
	@rm -f $(NAME)
	@echo "Cleaned all libraries"

re: fclean all

.PHONY: all clean fclean re
