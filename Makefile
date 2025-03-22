INCLUDE_DIR = include
SRC_DIR = src
TEST_DIR = test
EXE_NAME = colouring
UNIT_TEST_EXE_NAME = test_colouring

compile: $(SRC_DIR)/*.c
	g++ $(SRC_DIR)/*.c -I$(INCLUDE_DIR) -o $(EXE_NAME)

debug: $(SRC_DIR)/*.c
	g++ -g $(SRC_DIR)/*.c -I$(INCLUDE_DIR) -o $(EXE_NAME)

compile_test: $(SRC_DIR)/*.c
	g++ $(TEST_DIR)/*.c $(filter-out $(SRC_DIR)/colouring.c, $(wildcard SRC_DIR/*.c)) -I$(INCLUDE_DIR) -o $(UNIT_TEST_EXE_NAME)