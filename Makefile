VULKAN_SDK_PATH = "C:/VulkanSDK/1.4.304.0"
GLFW3_PATH = "C:/glfw-3.4_64"

CFLAGS = /std:c++20 /EHsc /I. /I$(VULKAN_SDK_PATH)/Include /I$(GLFW3_PATH)/include /Isrc
LDFLAGS = /link /LIBPATH:$(VULKAN_SDK_PATH)/lib /LIBPATH:$(GLFW3_PATH)/lib-vc2022 vulkan-1.lib glfw3.lib glfw3_mt.lib glfw3dll.lib user32.lib gdi32.lib shell32.lib /NODEFAULTLIB:MSVCRT /NODEFAULTLIB:libucrt.lib ucrt.lib vcruntime.lib

BIN_DIR = bin
OBJ_DIR = $(BIN_DIR)
SHADER_DIR = shaders
SHADER_BIN_DIR = $(BIN_DIR)\$(SHADER_DIR)

SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp,$(OBJ_DIR)/%.obj,$(SOURCES))

VERT_SHADERS = $(wildcard $(SHADER_DIR)/*.vert)
FRAG_SHADERS = $(wildcard $(SHADER_DIR)/*.frag)
SPV_VERT_SHADERS = $(patsubst $(SHADER_DIR)/%.vert,$(SHADER_BIN_DIR)/%.vert.spv,$(VERT_SHADERS))
SPV_FRAG_SHADERS = $(patsubst $(SHADER_DIR)/%.frag,$(SHADER_BIN_DIR)/%.frag.spv,$(FRAG_SHADERS))

a.out: $(OBJECTS) $(SPV_VERT_SHADERS) $(SPV_FRAG_SHADERS) | $(BIN_DIR)
	link $(LDFLAGS) /OUT:$(BIN_DIR)/main.exe $(OBJECTS)

$(OBJ_DIR)/%.obj: src/%.cpp | $(BIN_DIR)
	cl $(CFLAGS) /c $< /Fo$@

$(SHADER_BIN_DIR)/%.vert.spv: $(SHADER_DIR)/%.vert | $(SHADER_BIN_DIR)
	"$(VULKAN_SDK_PATH)/Bin/glslc.exe" $< -o $@

$(SHADER_BIN_DIR)/%.frag.spv: $(SHADER_DIR)/%.frag | $(SHADER_BIN_DIR)
	"$(VULKAN_SDK_PATH)/Bin/glslc.exe" $< -o $@

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(SHADER_BIN_DIR):
	mkdir $(SHADER_BIN_DIR)

.PHONY: test clean all

# build new changes and run exe
test: a.out
	$(BIN_DIR)/main.exe

clean:
	del $(BIN_DIR)\main.exe
	del $(OBJ_DIR)\*.obj
	del $(SHADER_BIN_DIR)\*.spv

# first it cleans the bind directory, then recompile all and call the execuateble
all: clean test