INCLUDE_DIR = include
SRC_DIR = src
EXE_NAME = colouring

colouring: $(SRC_DIR)/*.c
	g++ $(SRC_DIR)/*.c -I$(INCLUDE_DIR) -o $(EXE_NAME)