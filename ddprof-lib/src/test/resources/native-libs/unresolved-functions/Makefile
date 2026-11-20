TARGET_DIR = ../build/test/resources/unresolved-functions
all:
	gcc -fPIC -c main.c -o $(TARGET_DIR)/main.o
	gcc -o $(TARGET_DIR)/main $(TARGET_DIR)/main.o -T linker.ld