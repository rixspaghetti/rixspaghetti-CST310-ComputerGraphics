# Cross platform settings
OS := $(shell uname)
ifeq ($(OS), Linux)
	LIBS := -lGL -lGLEW -lglfw -lGLU -lglut
	INCLUDES := -I/usr/include 
	LINKFLAGS := -L/usr/lib 
	INSTALL := sudo apt-get install -y
	PKG := glew glfw glut
else ifeq ($(OS), Darwin) # macOS
	LIBS := -lglew -lglfw -lglut -framework OpenGL
	INCLUDES := -I/opt/homebrew/include -I./SOIL 
	LINKFLAGS := -L/opt/homebrew/lib
	INSTALL := brew install
	PKG := glew glfw
else ifeq ($(OS), Windows_NT)
	LIBS := -lopengl32 -lglfw3 -lgdi32
	INCLUDES := -I./glad/include -I./SOIL
	LINKFLAGS := -L./glfw/lib -L./glew/lib
	INSTALL := vcpkg install
	PKG := glew glfw3
endif

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 $(INCLUDES)

# source files
SRC := main.cpp 

# Output file
OUT := main  

all: install=-dependencies compile 

install-dependencies:
ifeq ($(OS), Linux)
	$(INSTALL) $(PKG)
else ifeq ($(OS), Darwin)
	$(INSTALL) $(PKG)
else ifeq ($(OS), Windows_NT)
	$(INSTALL) $(PKG)
endif

compile:
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(LIBS) $(LINKFLAGS)
	
run: compile 
	./$(OUT)
	
clean: 
	rm -f $(OUT)


#./$(OUT)