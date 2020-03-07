cmake_minimum_required(VERSION 3.7)
project(OpenStrategia)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        include/GUI/Text/Character.hpp
        include/GUI/Text/LineBreak.hpp
        include/GUI/Button.hpp
        include/GUI/Checkbox.hpp
        include/GUI/Image.hpp
        include/GUI/MultiButton.hpp
        include/GUI/Slider.hpp
        include/GUI/Text.hpp
        include/Program/Shader.hpp
        include/Texture/TextureBMP.hpp
        include/Texture/TextureBridge.hpp
        include/Texture/TextureDDS.hpp
        include/Camera.hpp
        include/Font.hpp
        include/Global.hpp
        include/GUI.hpp
        include/Main.hpp
        include/Program.hpp
        include/Renderable.hpp
        include/RenderableComposite.hpp
        include/RenderableCompositeParallel.hpp
        include/RenderableCompositeSwitching.hpp
        include/RenderObject.hpp
        include/RenderObject2D.hpp
        include/RenderObject3D.hpp
        include/Texture.hpp
        src/GUI/Text/Character.cpp
        src/GUI/Text/LineBreak.cpp
        src/GUI/Checkbox.cpp
        src/GUI/Image.cpp
        src/GUI/Slider.cpp
        src/GUI/Text.cpp
        src/Program/Shader.cpp
        src/Texture/TextureBMP.cpp
        src/Texture/TextureBridge.cpp
        src/Texture/TextureDDS.cpp
        src/Camera.cpp
        src/Font.cpp
        src/Main.cpp
        src/Program.cpp
        src/Renderable.cpp
        src/RenderableComposite.cpp
        src/RenderableCompositeParallel.cpp
        src/RenderableCompositeSwitching.cpp
        src/RenderObject.cpp
        src/RenderObject2D.cpp
        src/RenderObject3D.cpp
        src/Texture.cpp
        Makefile)

add_executable(OpenStrategia ${SOURCE_FILES})