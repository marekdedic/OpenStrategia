LD = $(CXX)

CFLAGS_ALL = -Wnon-virtual-dtor -Winit-self -Wredundant-decls -Wcast-align -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -std=c++11 -Wfatal-errors -Wextra -Wall
LIB_ALL = -lfreetype

CFLAGS_WIN = $(CFLAGS_ALL) -DGLEW_STATIC
CFLAGS_LINUX = -I /usr/include/freetype2 $(CFLAGS_ALL)
LDFLAGS_WIN =
LDFLAGS_LINUX =
LIB_WIN = $(LIB_ALL) -lglfw3 -lmingw32 -lglew32s -lopengl32 -mwindows
LIB_LINUX = $(LIB_ALL) -lglfw -lpthread -lGL -lGLEW
EXEC_NAME_WIN = OpenStrategia.exe
EXEC_NAME_LINUX = OpenStrategia
RM_WIN = del /Q
RM_LINUX = rm -fr
MKDIR_WIN = for /F "tokens=* delims= " %%p in ("$(1)") do ( for %%b in (%%p) do ( if not exist %%b mkdir %%b ))
MKDIR_LINUX = mkdir -p $(1)

ifeq ($(OS),Windows_NT)
	CFLAGS = $(CFLAGS_WIN)
	LDFLAGS = $(LDFLAGS_WIN)
	LIB = $(LIB_WIN)
	EXEC_NAME = $(EXEC_NAME_WIN)
	RM = $(RM_WIN)
	MKDIR = $(MKDIR_WIN)
else
	CFLAGS = $(CFLAGS_LINUX)
	LDFLAGS = $(LDFLAGS_LINUX)
	LIB = $(LIB_LINUX)
	EXEC_NAME = $(EXEC_NAME_LINUX)
	RM = $(RM_LINUX)
	MKDIR = $(MKDIR_LINUX)
endif

SRCDIR = src
OBJDIR = obj
BINDIR = bin
ERRFILE = /ErrorLog.txt
CORE = /core
VALG_OUT = /valgrind-output.txt

CFLAGS_DEBUG = $(CFLAGS) -g
LDFLAGS_DEBUG = $(LDFLAGS)
LIB_DEBUG = $(LIB)
SRCDIR_DEBUG = $(SRCDIR)
OBJDIR_DEBUG = $(OBJDIR)/debug
OBJDIRS_DEBUG = $(OBJDIR_DEBUG)/GUI $(OBJDIR_DEBUG)/GUI/Text $(OBJDIR_DEBUG)/Program $(OBJDIR_DEBUG)/Texture
BINDIR_DEBUG = $(BINDIR)/debug
OUT_DEBUG = $(BINDIR_DEBUG)/$(EXEC_NAME)

CFLAGS_RELEASE = $(CFLAGS) -s -O3 -flto
LDFLAGS_RELEASE = $(LDFLAGS) -flto
LIB_RELEASE = $(LIB)
SRCDIR_RELEASE = $(SRCDIR)
OBJDIR_RELEASE = $(OBJDIR)/release
OBJDIRS_RELEASE = $(OBJDIR_RELEASE)/GUI $(OBJDIR_RELEASE)/GUI/Text $(OBJDIR_RELEASE)/Program $(OBJDIR_RELEASE)/Texture
BINDIR_RELEASE = $(BINDIR)/release
OUT_RELEASE = $(BINDIR_RELEASE)/$(EXEC_NAME)

CFLAGS_PROFILE = $(CFLAGS) -pg
LDFLAGS_PROFILE = $(LDFLAGS)
LIB_PROFILE = $(LIB) -pg
SRCDIR_PROFILE = $(SRCDIR)
OBJDIR_PROFILE = $(OBJDIR)/profile
OBJDIRS_PROFILE = $(OBJDIR_PROFILE)/GUI $(OBJDIR_PROFILE)/GUI/Text $(OBJDIR_PROFILE)/Program $(OBJDIR_PROFILE)/Texture
BINDIR_PROFILE = $(BINDIR)/profile
OUT_PROFILE = $(BINDIR_PROFILE)/$(EXEC_NAME)

OBJ_DEBUG = $(OBJDIR_DEBUG)/Camera.o $(OBJDIR_DEBUG)/GUI/Text/Character.o $(OBJDIR_DEBUG)/GUI/Checkbox.o $(OBJDIR_DEBUG)/Font.o $(OBJDIR_DEBUG)/GUI/Image.o $(OBJDIR_DEBUG)/GUI/Text/LineBreak.o $(OBJDIR_DEBUG)/Main.o $(OBJDIR_DEBUG)/Program.o $(OBJDIR_DEBUG)/Renderable.o $(OBJDIR_DEBUG)/RenderableComposite.o $(OBJDIR_DEBUG)/RenderableCompositeParallel.o $(OBJDIR_DEBUG)/RenderableCompositeSwitching.o $(OBJDIR_DEBUG)/RenderObject.o $(OBJDIR_DEBUG)/RenderObject2D.o $(OBJDIR_DEBUG)/RenderObject3D.o $(OBJDIR_DEBUG)/Program/Shader.o $(OBJDIR_DEBUG)/GUI/Slider.o $(OBJDIR_DEBUG)/GUI/Text.o $(OBJDIR_DEBUG)/Texture.o $(OBJDIR_DEBUG)/Texture/TextureBMP.o $(OBJDIR_DEBUG)/Texture/TextureBridge.o $(OBJDIR_DEBUG)/Texture/TextureDDS.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/Camera.o $(OBJDIR_RELEASE)/GUI/Text/Character.o $(OBJDIR_RELEASE)/GUI/Checkbox.o $(OBJDIR_RELEASE)/Font.o $(OBJDIR_RELEASE)/GUI/Image.o $(OBJDIR_RELEASE)/GUI/Text/LineBreak.o $(OBJDIR_RELEASE)/Main.o $(OBJDIR_RELEASE)/Program.o $(OBJDIR_RELEASE)/Renderable.o $(OBJDIR_RELEASE)/RenderableComposite.o $(OBJDIR_RELEASE)/RenderableCompositeParallel.o $(OBJDIR_RELEASE)/RenderableCompositeSwitching.o $(OBJDIR_RELEASE)/RenderObject.o $(OBJDIR_RELEASE)/RenderObject2D.o $(OBJDIR_RELEASE)/RenderObject3D.o $(OBJDIR_RELEASE)/Program/Shader.o $(OBJDIR_RELEASE)/GUI/Slider.o $(OBJDIR_RELEASE)/GUI/Text.o $(OBJDIR_RELEASE)/Texture.o $(OBJDIR_RELEASE)/Texture/TextureBMP.o $(OBJDIR_RELEASE)/Texture/TextureBridge.o $(OBJDIR_RELEASE)/Texture/TextureDDS.o

OBJ_PROFILE = $(OBJDIR_PROFILE)/Camera.o $(OBJDIR_PROFILE)/GUI/Text/Character.o $(OBJDIR_PROFILE)/GUI/Checkbox.o $(OBJDIR_PROFILE)/Font.o $(OBJDIR_PROFILE)/GUI/Image.o $(OBJDIR_PROFILE)/GUI/Text/LineBreak.o $(OBJDIR_PROFILE)/Main.o $(OBJDIR_PROFILE)/Program.o $(OBJDIR_PROFILE)/Renderable.o $(OBJDIR_PROFILE)/RenderableComposite.o $(OBJDIR_PROFILE)/RenderableCompositeParallel.o $(OBJDIR_PROFILE)/RenderableCompositeSwitching.o $(OBJDIR_PROFILE)/RenderObject.o $(OBJDIR_PROFILE)/RenderObject2D.o $(OBJDIR_PROFILE)/RenderObject3D.o $(OBJDIR_PROFILE)/Program/Shader.o $(OBJDIR_PROFILE)/GUI/Slider.o $(OBJDIR_PROFILE)/GUI/Text.o $(OBJDIR_PROFILE)/Texture.o $(OBJDIR_PROFILE)/Texture/TextureBMP.o $(OBJDIR_PROFILE)/Texture/TextureBridge.o $(OBJDIR_PROFILE)/Texture/TextureDDS.o

ifeq ($(OS),Windows_NT)
	ERRFILE ::= $(strip $(subst /,\, $(ERRFILE)))
	CORE ::= $(strip $(subst /,\, $(CORE)))
	VALG_OUT ::= $(strip $(subst /,\, $(VALG_OUT)))
	OBJDIR_DEBUG ::= $(subst /,\, $(OBJDIR_DEBUG))
	OBJDIRS_DEBUG ::= $(subst /,\, $(OBJDIRS_DEBUG))
	BINDIR_DEBUG ::= $(subst /,\, $(BINDIR_DEBUG))
	OUT_DEBUG ::= $(subst /,\, $(OUT_DEBUG))
	OBJDIR_RELEASE ::= $(subst /,\, $(OBJDIR_RELEASE))
	OBJDIRS_RELEASE ::= $(subst /,\, $(OBJDIRS_RELEASE))
	BINDIR_RELEASE ::= $(subst /,\, $(BINDIR_RELEASE))
	OUT_RELEASE ::= $(subst /,\, $(OUT_RELEASE))
	OBJDIR_PROFILE ::= $(subst /,\, $(OBJDIR_PROFILE))
	OBJDIRS_PROFILE ::= $(subst /,\, $(OBJDIRS_PROFILE))
	BINDIR_PROFILE ::= $(subst /,\, $(BINDIR_PROFILE))
	OUT_PROFILE ::= $(subst /,\, $(OUT_PROFILE))
endif

.DEFAULT_GOAL := help

setup: ## Setup development environment
	@./initialize.sh

all: debug release profile ## Build all build targets

clean: clean_debug clean_release clean_profile ## Clean all build files

before_debug:
	$(call MKDIR, $(OBJDIR_DEBUG))
	$(call MKDIR, $(OBJDIRS_DEBUG))
	$(call MKDIR, $(BINDIR_DEBUG))

debug: before_debug out_debug ## Build the "debug" target

out_debug: $(OBJ_DEBUG)
	$(LD) $(LDFLAGS_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/%.o: $(SRCDIR_DEBUG)/%.cpp
	$(CXX) $(CFLAGS_DEBUG) -c $< -o $@

clean_debug: ## Clean build files for the "debug" target
	$(RM) $(OBJDIR_DEBUG)
	$(RM) $(OBJDIRS_DEBUG)
	$(RM) $(BINDIR_DEBUG)$(ERRFILE)
	$(RM) $(BINDIR_DEBUG)$(CORE)
	$(RM) $(BINDIR_DEBUG)$(VALG_OUT)
	$(RM) $(OUT_DEBUG)

$(OUT_DEBUG): debug

run_debug: $(OUT_DEBUG) ## Run OpenStrategia "debug" target
	(cd $(BINDIR_DEBUG) ; ./$(EXEC_NAME))

before_release:
	$(call MKDIR, $(OBJDIR_RELEASE))
	$(call MKDIR, $(OBJDIRS_RELEASE))
	$(call MKDIR, $(BINDIR_RELEASE))

release: before_release out_release ## Build the "release" target

out_release: $(OBJ_RELEASE)
	$(LD) $(LDFLAGS_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/%.o: $(SRCDIR_RELEASE)/%.cpp
	$(CXX) $(CFLAGS_RELEASE) -c $< -o $@

clean_release: ## Clean build files for the "release" target
	$(RM) $(OBJDIR_RELEASE)
	$(RM) $(OBJDIRS_RELEASE)
	$(RM) $(BINDIR_RELEASE)$(ERRFILE)
	$(RM) $(BINDIR_RELEASE)$(CORE)
	$(RM) $(OUT_RELEASE)

$(OUT_RELEASE): release

run_release: $(OUT_RELEASE) ## Run OpenStrategia "release" target
	(cd $(BINDIR_RELEASE) ; ./$(EXEC_NAME))

before_profile:
	$(call MKDIR, $(OBJDIR_PROFILE))
	$(call MKDIR, $(OBJDIRS_PROFILE))
	$(call MKDIR, $(BINDIR_PROFILE))

profile: before_profile out_profile ## Build the "profile" target

out_profile: $(OBJ_PROFILE)
	$(LD) $(LDFLAGS_PROFILE) -o $(OUT_PROFILE) $(OBJ_PROFILE) $(LIB_PROFILE)

$(OBJDIR_PROFILE)/%.o: $(SRCDIR_PROFILE)/%.cpp
	$(CXX) $(CFLAGS_PROFILE) -c $< -o $@

clean_profile: ## Clean build files for the "profile" target
	$(RM) $(OBJDIR_PROFILE)
	$(RM) $(OBJDIRS_PROFILE)
	$(RM) $(BINDIR_PROFILE)$(ERRFILE)
	$(RM) $(BINDIR_PROFILE)$(CORE)
	$(RM) $(OUT_PROFILE)

$(OUT_PROFILE): profile

run_profile: $(OUT_PROFILE) ## Run OpenStrategia "profile" target
	(cd $(BINDIR_PROFILE) ; ./$(EXEC_NAME))

run: run_release ## Run OpenStrategia (default target is "release")

help: ## Print this help
ifeq ($(OS),Windows_NT)
	echo "Help not supported on Windows. Please run \"make all\"."
else
	@printf "\033[0;31mIf you don't know what you are doing, just run \"make setup\", followed by \"make run\".\033[0m\n"
	@grep -E '^[a-zA-Z0-9_-]+:.*?##.*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
endif

.PHONY: all help clean before_debug debug out_debug clean_debug before_release release out_release clean_release before_profile profile out_profile clean_profile
