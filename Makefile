# Compiler and flags
CC = cc
CXX = x86_64-w64-mingw32-g++
CFLAGS = -Wall
LDFLAGS = -I/home/cashcraf/raylib/src -L/home/cashcraf/raylib/src
LIBS_LINUX = -lraylib -lGL -lpthread -ldl -lrt -lX11 -lm
LIBS_WINDOWS = -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread -O1

# Source files
SRC = $(wildcard *.cc)

# Output executables
OUT_LINUX = waffle.exe
OUT_WINDOWS = window.exe

all: linux windows

linux: $(OUT_LINUX)

windows: $(OUT_WINDOWS)

$(OUT_LINUX): $(OBJ)
	$(CC) -o $(OUT_LINUX) $^ $(LDFLAGS) $(LIBS_LINUX)

$(OUT_WINDOWS): $(OBJ)
	$(CXX) -o $(OUT_WINDOWS) $^ $(CFLAGS) $(LDFLAGS) $(LIBS_WINDOWS)

%.o: %.cc
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

.PHONY: run clean

run: linux
	./$(OUT_LINUX)

clean:
	rm -f $(OUT_LINUX) $(OUT_WINDOWS) $(OBJ)
