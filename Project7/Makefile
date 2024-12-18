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
	INCLUDES := -I/opt/homebrew/include -I./SOIL -I./glad/include
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
SRC := CheckeredTriangles2.cpp ./glad/src/glad.c
SRC2 := ColorCubeFlyBy2.cpp ./glad/src/glad.c



# Output file
OUT := checkered 
OUT2 := cubefly  


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
	$(CXX) $(CXXFLAGS) -o $(OUT2) $(SRC2) $(LIBS) $(LINKFLAGS)

run: compile 
	./$(OUT)
	./$(OUT2)

clean: 
	rm -f $(OUT)
	rm -f $(OUT2)


#./$(OUT)