INCLUDE_DIR = include
SRC_DIR = src
TEST_DIR = test
TEST_FILES = $(SRC_DIR)/graphutil.c
EXE_NAME = colouring

compile: $(SRC_DIR)/*.c
	g++ $(SRC_DIR)/*.c -I$(INCLUDE_DIR) -o $(EXE_NAME)

test: $(TEST_DIR)/*.c
	g++ $(TEST_DIR)/*.c $(TEST_FILES) -I$(INCLUDE_DIR) -o test$(EXE_NAME)
