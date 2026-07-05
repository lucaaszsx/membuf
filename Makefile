PROJ_NAME=membuf

# folders
SRC=./src
BUILD=./build

# files
C_SRC=$(wildcard $(SRC)/*.c)
H_SRC=$(wildcard $(SRC)/*.h)

# obj files
OBJ=$(subst .c,.o,$(subst $(SRC),$(BUILD),$(C_SRC)))

# compiler
CC=gcc
CC_FLAGS=-c

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) $^ -o $@

$(BUILD):
	mkdir $(BUILD) -p

$(BUILD)/%.o: $(SRC)/%.c | $(BUILD)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	@ rm -rf $(BUILD)/*.o $(PROJ_NAME) ~*
	@ rmdir $(BUILD)

run: all
	./$(PROJ_NAME)

.PHONY: all clean run
