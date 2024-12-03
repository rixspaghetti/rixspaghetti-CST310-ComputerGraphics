# Cross platform settings
OS := $(shell uname)
ifeq ($(OS), Linux)
	LIBS := -lGL -lGLEW -lglfw -lGLU -lglut -lassimp
	INCLUDES := -I/usr/include 
	LINKFLAGS := -L/usr/lib 
	INSTALL := sudo apt-get install -y
	PKG := glew glfw glut assimp
else ifeq ($(OS), Darwin) # macOS
	LIBS := -lglew -lglfw -lglut -framework OpenGL -L/Users/rix/SOIL -L/opt/homebrew/lib -lassimp
	INCLUDES := -I/opt/homebrew/include -I/Users/rix/glad/include -I/Users/rix/SOIL/src
	LINKFLAGS := -L/opt/homebrew/lib -arch i386 -arch x86_64 -arch arm64
	INSTALL := brew install
	PKG := glew glfw assimp
else ifeq ($(OS), Windows_NT)
	LIBS := -lopengl32 -lglfw3 -lgdi32 -lassimp
	INCLUDES := -I/Users/rix/glad/include -I/Users/rix/SOIL/src
	LINKFLAGS := -L./glfw/lib -L./glew/lib
	INSTALL := vcpkg install
	PKG := glew glfw3 assimp
endif

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++11 $(INCLUDES) -arch i386 -arch x86_64 -arch arm64

# Source files
SRC := main.cpp /Users/rix/glad/src/glad.c

# Output file
OUT := main  

all: install-dependencies compile 

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
