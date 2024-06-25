# Compiler
CC_BIN = g++
CC_STD = -std=c++11
CC_WRN = -Wall
CC_INC = -I..
CC_DEF = -D_DOGFOOD_UNIT_TEST

# File Extensions
EXT_CPP  = cpp
EXT_TEST = unittest

# Directories
DIR_TEST    = .
DIR_INCLUDE = .
DIR_BIN     = bin

# Targets
TGT_TEST := $(wildcard $(DIR_TEST)/*.$(EXT_TEST).$(EXT_CPP))

# Binaries
BIN_TEST := $(TGT_TEST:$(DIR_TEST)/%.$(EXT_CPP)=$(DIR_BIN)/%)

# Run tests
test: $(BIN_TEST)

clean:
	@rm -rf $(DIR_BIN)/*.$(EXT_TEST)

# Build each test
$(BIN_TEST) : $(DIR_BIN)/% : $(DIR_TEST)/%.$(EXT_CPP)
	@mkdir -p $(DIR_BIN)
	@$(CC_BIN) $(CC_STD) $(CC_WRN) $(CC_DEF) $(CC_INC) $< -g -o $@
	@echo "Unit Test: $<"
	@./$@
