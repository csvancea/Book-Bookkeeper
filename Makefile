CXXFLAGS = -c -Wall -Wextra -std=c++17 -DFMT_HEADER_ONLY -I./include
# CXXFLAGS += -g -DENABLE_LOGGING
# CXXFLAGS += -O2 -march=native -mtune=native
LDFLAGS =

EXE_NAME = tema3pc

SRC_DIR = src
OUT_DIR = build/linux
OBJ_DIR = $(OUT_DIR)/obj
OUT_EXE = $(OUT_DIR)/$(EXE_NAME)

SRC_FILES = $(shell find $(SRC_DIR)/ -type f -name '*.cpp')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))


.PHONY: build
build: $(OUT_EXE)

.PHONY: run
run: build
	./$(OUT_EXE)

.PHONY: clean
clean:
	rm -rf "$(OUT_DIR)" "$(OBJ_DIR)"

$(OUT_EXE): $(OBJ_FILES)
	@mkdir -p "$(OUT_DIR)"
	@echo Linking "$(OUT_EXE)" ...
	@$(CXX) $(LDFLAGS) -o "$(OUT_EXE)" $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p "$(@D)"
	@echo Compiling "$<" ...
	@$(CXX) $(CXXFLAGS) -o $@ $<
