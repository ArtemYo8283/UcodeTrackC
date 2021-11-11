NAME = libmx.a
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(INC_DIR)/*.h)
CC = clang
CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic) -g
AR = ar
AFLAGS = rcs
MKDIR = mkdir -p
RM = rm -rf

all: $(NAME) clean

$(NAME): $(OBJ_FILES)
	@$(AR) $(AFLAGS) $@ $^

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ_DIR):
	@$(MKDIR) $@

clean:
	@$(RM) $(OBJ_DIR)

uninstall:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)

reinstall: uninstall all

.PHONY: all uninstall clean reinstall

