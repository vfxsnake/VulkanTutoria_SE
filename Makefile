CC = cl.exe
LD = link.exe

# Compiler flags
CFLAGS = /EHsc /MD /std:c++20 /D__INTELLISENSE__

# Include paths
INCLUDE_PATHS = \
    /IC:/VulkanSDK/1.4.313.2/Include \
    /IC:/DEV/glfw_3.4_x64/include

# Library paths
LIB_PATHS = \
    /LIBPATH:C:/VulkanSDK/1.4.313.2/Lib \
    /LIBPATH:C:/DEV/glfw_3.4_x64/lib-vc2022

# Libraries
LIBS = \
    vulkan-1.lib \
    glfw3.lib \
    gdi32.lib \
    shell32.lib \
    user32.lib \
    legacy_stdio_definitions.lib

# Output directories
BIN_DIR = bin
OBJ_DIR = obj

# Source files
SRCS = src/main.cpp

# Object files
OBJS = $(patsubst src/%.cpp,$(OBJ_DIR)/%.obj,$(SRCS))

# Executable name
TARGET = $(BIN_DIR)/main.exe

.PHONY: all clean run

all: $(TARGET)

run: all
	@echo Running $(TARGET)...
	$(TARGET)

$(TARGET): $(OBJS)
	@echo Creating $(BIN_DIR) directory if it does not exist...
	@if not exist $(BIN_DIR) mkdir $(BIN_DIR)
	$(LD) $(LIB_PATHS) $(LIBS) /out:$@ $(OBJS)

$(OBJ_DIR)/%.obj: src/%.cpp
	@echo Creating $(OBJ_DIR) directory if it does not exist...
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) /c $< /Fo$@

clean:
	@echo Cleaning up...
	-@del /Q $(OBJS) $(TARGET) 2>nul
	-@rmdir /S /Q $(OBJ_DIR) 2>nul
	-@rmdir /S /Q $(BIN_DIR) 2>nul
