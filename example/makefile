# Compiler
CPP_BIN = g++
CPP_STD = -std=c++11
CPP_WRN = -Wall
CPP_INC = -I..

# File Extensions
EXT_CPP  = cpp

# Directories
DIR_INCLUDE = ..
DIR_SRC     = .
DIR_BIN     = bin

all:
	make simple_example_linux_uds
	make simple_example
	make simple_example_udp

simple_example_linux_uds:
	@echo "Building simple_example_linux_uds"
	@mkdir -p bin
	@$(CPP_BIN) $(CPP_STD) $(CPP_WRN) $(CPP_INC) simple_example_linux_uds.cpp -o bin/simple_example_linux_uds

simple_example:
	@echo "Building simple_example"
	@mkdir -p bin
	@$(CPP_BIN) $(CPP_STD) $(CPP_WRN) $(CPP_INC) simple_example.cpp -o bin/simple_example

simple_example_udp:
	@echo "Building simple_example_udp"
	@mkdir -p bin
	@$(CPP_BIN) $(CPP_STD) $(CPP_WRN) $(CPP_INC) simple_example_udp.cpp -o bin/simple_example_udp

clean:
	@rm -rf $(DIR_BIN)/*