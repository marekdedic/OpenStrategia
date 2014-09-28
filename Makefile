CFLAGS = -Wnon-virtual-dtor -Winit-self -Wredundant-decls -Wcast-align -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -std=c++11 -Wfatal-errors -Wextra -Wall
LIB = -lglfw3 -lGLEW -lGL -lX11 -lXxf86vm -lpthread -lXrandr -lXi
OBJDIR = obj
BINDIR = bin

CFLAGS_DEBUG = $(CFLAGS) -g
LIB_DEBUG = $(LIB)
OBJDIR_DEBUG = $(OBJDIR)/Debug
BINDIR_DEBUG = $(BINDIR)/Debug
OUT_DEBUG = $(BINDIR_DEBUG)/OpenStrategia

CFLAGS_RELEASE = $(CFLAGS) -s -O3
LIB_RELEASE = $(LIB)
OBJDIR_RELEASE = $(OBJDIR)/Release
BINDIR_RELEAsE = $(BINDIR)/Release
OUT_RELEASE = $(BINDIR_RELEASE)/OpenStrategia

CFLAGS_PROFILE = $(CFLAGS) -pg
LIB_PROFILE = $(LIB)
OBJDIR_PROFILE = $(OBJDIR)/Profile
BINDIR_PROFILE = $(BINDIR)/Profile
OUT_PROFILE = $(BINDIR_PROFILE)/OpenStrategia

OBJ_DEBUG = $(OBJDIR_DEBUG)/Button.o $(OBJDIR_DEBUG)/Camera.o $(OBJDIR_DEBUG)/Checkbox.o $(OBJDIR_DEBUG)/Image.o $(OBJDIR_DEBUG)/Main.o $(OBJDIR_DEBUG)/Program.o $(OBJDIR_DEBUG)/RenderObject.o $(OBJDIR_DEBUG)/RenderObject2D.o $(OBJDIR_DEBUG)/RenderObject3D.o $(OBJDIR_DEBUG)/Shader.o $(OBJDIR_DEBUG)/Texture.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/Button.o $(OBJDIR_RELEASE)/Camera.o $(OBJDIR_RELEASE)/Checkbox.o $(OBJDIR_RELEASE)/Image.o $(OBJDIR_RELEASE)/Main.o $(OBJDIR_RELEASE)/Program.o $(OBJDIR_RELEASE)/RenderObject.o $(OBJDIR_RELEASE)/RenderObject2D.o $(OBJDIR_RELEASE)/RenderObject3D.o $(OBJDIR_RELEASE)/Shader.o $(OBJDIR_RELEASE)/Texture.o

OBJ_PROFILE = $(OBJDIR_PROFILE)/Button.o $(OBJDIR_PROFILE)/Camera.o $(OBJDIR_PROFILE)/Checkbox.o $(OBJDIR_PROFILE)/Image.o $(OBJDIR_PROFILE)/Main.o $(OBJDIR_PROFILE)/Program.o $(OBJDIR_PROFILE)/RenderObject.o $(OBJDIR_PROFILE)/RenderObject2D.o $(OBJDIR_PROFILE)/RenderObject3D.o $(OBJDIR_PROFILE)/Shader.o $(OBJDIR_PROFILE)/Texture.o

all: debug release profile

clean: clean_debug clean_release clean_profile

before_debug:
	test -d $(BINDIR_DEBUG) || mkdir -p $(BINDIR_DEBUG)
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

debug: before_debug out_debug

out_debug: $(OBJ_DEBUG)
	$(LD) -o $(OUT_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/Button.o: Button.cpp
	$(CXX) $(CFLAGS_DEBUG) -c Button.cpp -o $(OBJDIR_DEBUG)/Button.o

$(OBJDIR_DEBUG)/Camera.o: Camera.cpp
	$(CXX) $(CFLAGS_DEBUG) -c Camera.cpp -o $(OBJDIR_DEBUG)/Camera.o

$(OBJDIR_DEBUG)/Checkbox.o: Checkbox.cpp
	$(CXX) $(CFLAGS_DEBUG) -c Checkbox.cpp -o $(OBJDIR_DEBUG)/Checkbox.o

$(OBJDIR_DEBUG)/Image.o: Image.cpp
	$(CXX) $(CFLAGS_DEBUG) -c Image.cpp -o $(OBJDIR_DEBUG)/Image.o

$(OBJDIR_DEBUG)/Main.o: Main.cpp
	$(CXX) $(CFLAGS_DEBUG) -c Main.cpp -o $(OBJDIR_DEBUG)/Main.o

$(OBJDIR_DEBUG)/Program.o: Program.cpp
	$(CXX) $(CFLAGS_DEBUG) -c Program.cpp -o $(OBJDIR_DEBUG)/Program.o

$(OBJDIR_DEBUG)/RenderObject.o: RenderObject.cpp
	$(CXX) $(CFLAGS_DEBUG) -c RenderObject.cpp -o $(OBJDIR_DEBUG)/RenderObject.o

$(OBJDIR_DEBUG)/RenderObject2D.o: RenderObject2D.cpp
	$(CXX) $(CFLAGS_DEBUG) -c RenderObject2D.cpp -o $(OBJDIR_DEBUG)/RenderObject2D.o

$(OBJDIR_DEBUG)/RenderObject3D.o: RenderObject3D.cpp
	$(CXX) $(CFLAGS_DEBUG) -c RenderObject3D.cpp -o $(OBJDIR_DEBUG)/RenderObject3D.o

$(OBJDIR_DEBUG)/Shader.o: Shader.cpp
	$(CXX) $(CFLAGS_DEBUG) -c Shader.cpp -o $(OBJDIR_DEBUG)/Shader.o

$(OBJDIR_DEBUG)/Texture.o: Texture.cpp
	$(CXX) $(CFLAGS_DEBUG) -c Texture.cpp -o $(OBJDIR_DEBUG)/Texture.o

clean_debug:
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf $(BINDIR_DEBUG)
	rm -rf $(OBJDIR_DEBUG)

before_release:
	test -d $(BINDIR_RELEASE) || mkdir -p $(BINDIR_RELESE)
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

release: before_release out_release

out_release: before_release $(OBJ_RELEASE)
	$(LD) -o $(OUT_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/Button.o: Button.cpp
	$(CXX) $(CFLAGS_RELEASE) -c Button.cpp -o $(OBJDIR_RELEASE)/Button.o

$(OBJDIR_RELEASE)/Camera.o: Camera.cpp
	$(CXX) $(CFLAGS_RELEASE) -c Camera.cpp -o $(OBJDIR_RELEASE)/Camera.o

$(OBJDIR_RELEASE)/Checkbox.o: Checkbox.cpp
	$(CXX) $(CFLAGS_RELEASE) -c Checkbox.cpp -o $(OBJDIR_RELEASE)/Checkbox.o

$(OBJDIR_RELEASE)/Image.o: Image.cpp
	$(CXX) $(CFLAGS_RELEASE) -c Image.cpp -o $(OBJDIR_RELEASE)/Image.o

$(OBJDIR_RELEASE)/Main.o: Main.cpp
	$(CXX) $(CFLAGS_RELEASE) -c Main.cpp -o $(OBJDIR_RELEASE)/Main.o

$(OBJDIR_RELEASE)/Program.o: Program.cpp
	$(CXX) $(CFLAGS_RELEASE) -c Program.cpp -o $(OBJDIR_RELEASE)/Program.o

$(OBJDIR_RELEASE)/RenderObject.o: RenderObject.cpp
	$(CXX) $(CFLAGS_RELEASE) -c RenderObject.cpp -o $(OBJDIR_RELEASE)/RenderObject.o

$(OBJDIR_RELEASE)/RenderObject2D.o: RenderObject2D.cpp
	$(CXX) $(CFLAGS_RELEASE) -c RenderObject2D.cpp -o $(OBJDIR_RELEASE)/RenderObject2D.o

$(OBJDIR_RELEASE)/RenderObject3D.o: RenderObject3D.cpp
	$(CXX) $(CFLAGS_RELEASE) -c RenderObject3D.cpp -o $(OBJDIR_RELEASE)/RenderObject3D.o

$(OBJDIR_RELEASE)/Shader.o: Shader.cpp
	$(CXX) $(CFLAGS_RELEASE) -c Shader.cpp -o $(OBJDIR_RELEASE)/Shader.o

$(OBJDIR_RELEASE)/Texture.o: Texture.cpp
	$(CXX) $(CFLAGS_RELEASE) -c Texture.cpp -o $(OBJDIR_RELEASE)/Texture.o

clean_release:
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf $(BINDIR_RELEASE)
	rm -rf $(OBJDIR_RELEASE)

before_profile:
	test -d $(BINDIR_PROFILE) || mkdir -p $(BINDIR_PROFILE)
	test -d $(OBJDIR_PROFILE) || mkdir -p $(OBJDIR_PROFILE)

debug: before_profile out_profile

out_profile: $(OBJ_PROFILE)
	$(LD) -o $(OUT_PROFILE) $(OBJ_PROFILE) $(LIB_PROFILE)

$(OBJDIR_PROFILE)/Button.o: Button.cpp
	$(CXX) $(CFLAGS_PROFILE) -c Button.cpp -o $(OBJDIR_PROFILE)/Button.o

$(OBJDIR_PROFILE)/Camera.o: Camera.cpp
	$(CXX) $(CFLAGS_PROFILE) -c Camera.cpp -o $(OBJDIR_PROFILE)/Camera.o

$(OBJDIR_PROFILE)/Checkbox.o: Checkbox.cpp
	$(CXX) $(CFLAGS_PROFILE) -c Checkbox.cpp -o $(OBJDIR_PROFILE)/Checkbox.o

$(OBJDIR_PROFILE)/Image.o: Image.cpp
	$(CXX) $(CFLAGS_PROFILE) -c Image.cpp -o $(OBJDIR_PROFILE)/Image.o

$(OBJDIR_PROFILE)/Main.o: Main.cpp
	$(CXX) $(CFLAGS_PROFILE) -c Main.cpp -o $(OBJDIR_PROFILE)/Main.o

$(OBJDIR_PROFILE)/Program.o: Program.cpp
	$(CXX) $(CFLAGS_PROFILE) -c Program.cpp -o $(OBJDIR_PROFILE)/Program.o

$(OBJDIR_PROFILE)/RenderObject.o: RenderObject.cpp
	$(CXX) $(CFLAGS_PROFILE) -c RenderObject.cpp -o $(OBJDIR_PROFILE)/RenderObject.o

$(OBJDIR_PROFILE)/RenderObject2D.o: RenderObject2D.cpp
	$(CXX) $(CFLAGS_PROFILE) -c RenderObject2D.cpp -o $(OBJDIR_PROFILE)/RenderObject2D.o

$(OBJDIR_PROFILE)/RenderObject3D.o: RenderObject3D.cpp
	$(CXX) $(CFLAGS_PROFILE) -c RenderObject3D.cpp -o $(OBJDIR_PROFILE)/RenderObject3D.o

$(OBJDIR_PROFILE)/Shader.o: Shader.cpp
	$(CXX) $(CFLAGS_PROFILE) -c Shader.cpp -o $(OBJDIR_PROFILE)/Shader.o

$(OBJDIR_PROFILE)/Texture.o: Texture.cpp
	$(CXX) $(CFLAGS_PROFILE) -c Texture.cpp -o $(OBJDIR_PROFILE)/Texture.o

clean_profile:
	rm -f $(OBJ_PROFILE) $(OUT_PROFILE)
	rm -rf $(BINDIR_PROFILE)
	rm -rf $(OBJDIR_PROFILE)


.PHONY: before_debug clean_debug before_release clean_release before_profile clean_profile

