SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

TARGET = tmatrix
CXX = g++
CXXFLAGS = -std=c++17 -Wall
CPPFLAGS = -I$(INC_DIR)
LDLIBS = -lncurses

.PHONY: clean

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	-rm -rf $(OBJ_DIR)
	-rm -f $(TARGET)
