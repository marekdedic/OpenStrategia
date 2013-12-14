#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = %cd%

CC = gcc.exe
CXX = g++.exe
AR = ar.exe
LD = g++.exe
WINDRES = windres.exe

INC = -IC:\\MinGW\\GLFW\\include
CFLAGS = -Wall
RESINC = 
LIBDIR = -LC:\\MinGW\\GLFW\\lib
LIB = -lglfw -lopengl32 -lglu32 -lgdi32 -lglew32
LDFLAGS = 

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj\\Debug
DEP_DEBUG = 
OUT_DEBUG = bin\\Debug\\OpenStrategia.exe

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj\\Release
DEP_RELEASE = 
OUT_RELEASE = bin\\Release\\OpenStrategia.exe

OBJ_DEBUG = $(OBJDIR_DEBUG)\\Main.o $(OBJDIR_DEBUG)\\Program.o $(OBJDIR_DEBUG)\\RenderObject.o $(OBJDIR_DEBUG)\\RenderObject2D.o $(OBJDIR_DEBUG)\\RenderObject3D.o $(OBJDIR_DEBUG)\\Shader.o

OBJ_RELEASE = $(OBJDIR_RELEASE)\\Main.o $(OBJDIR_RELEASE)\\Program.o $(OBJDIR_RELEASE)\\RenderObject.o $(OBJDIR_RELEASE)\\RenderObject2D.o $(OBJDIR_RELEASE)\\RenderObject3D.o $(OBJDIR_RELEASE)\\Shader.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	cmd /c if not exist bin\\Debug md bin\\Debug
	cmd /c if not exist $(OBJDIR_DEBUG) md $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)\\Main.o: Main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Main.cpp -o $(OBJDIR_DEBUG)\\Main.o

$(OBJDIR_DEBUG)\\Program.o: Program.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Program.cpp -o $(OBJDIR_DEBUG)\\Program.o

$(OBJDIR_DEBUG)\\RenderObject.o: RenderObject.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c RenderObject.cpp -o $(OBJDIR_DEBUG)\\RenderObject.o

$(OBJDIR_DEBUG)\\RenderObject2D.o: RenderObject2D.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c RenderObject2D.cpp -o $(OBJDIR_DEBUG)\\RenderObject2D.o

$(OBJDIR_DEBUG)\\RenderObject3D.o: RenderObject3D.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c RenderObject3D.cpp -o $(OBJDIR_DEBUG)\\RenderObject3D.o

$(OBJDIR_DEBUG)\\Shader.o: Shader.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c Shader.cpp -o $(OBJDIR_DEBUG)\\Shader.o

clean_debug: 
	cmd /c del /f $(OBJ_DEBUG) $(OUT_DEBUG)
	cmd /c rd bin\\Debug
	cmd /c rd $(OBJDIR_DEBUG)

before_release: 
	cmd /c if not exist bin\\Release md bin\\Release
	cmd /c if not exist $(OBJDIR_RELEASE) md $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) -mwindows $(LIB_RELEASE)

$(OBJDIR_RELEASE)\\Main.o: Main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Main.cpp -o $(OBJDIR_RELEASE)\\Main.o

$(OBJDIR_RELEASE)\\Program.o: Program.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Program.cpp -o $(OBJDIR_RELEASE)\\Program.o

$(OBJDIR_RELEASE)\\RenderObject.o: RenderObject.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c RenderObject.cpp -o $(OBJDIR_RELEASE)\\RenderObject.o

$(OBJDIR_RELEASE)\\RenderObject2D.o: RenderObject2D.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c RenderObject2D.cpp -o $(OBJDIR_RELEASE)\\RenderObject2D.o

$(OBJDIR_RELEASE)\\RenderObject3D.o: RenderObject3D.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c RenderObject3D.cpp -o $(OBJDIR_RELEASE)\\RenderObject3D.o

$(OBJDIR_RELEASE)\\Shader.o: Shader.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c Shader.cpp -o $(OBJDIR_RELEASE)\\Shader.o

clean_release: 
	cmd /c del /f $(OBJ_RELEASE) $(OUT_RELEASE)
	cmd /c rd bin\\Release
	cmd /c rd $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

