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

# Targets
TGT_BIN := $(wildcard $(DIR_SRC)/*.$(EXT_CPP))

# Binaries
BIN_EXAMPLE := $(TGT_BIN:$(DIR_SRC)/%.$(EXT_CPP)=$(DIR_BIN)/%)

$(BIN_EXAMPLE): $(DIR_BIN)/% : $(DIR_SRC)/%.$(EXT_CPP)
	@mkdir -p bin
	@$(CPP_BIN) $(CPP_STD) $(CPP_WRN) $(CPP_INC) -c $< -o $@

clean:
	@rm -rf $(DIR_BIN)/*