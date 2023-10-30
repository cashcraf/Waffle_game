# Compiler and flags
CC = g++
CXX = x86_64-w64-mingw32-g++
CFLAGS = -Wall
LDFLAGS = -I/home/cashcraf/raylib/src -L/home/cashcraf/raylib/src
LIBS_LINUX = -lraylib -lGL -lpthread -ldl -lrt -lX11 -lm
LIBS_WINDOWS = -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
OPT_FLAGS = -O1  # Adjust optimization level as needed

# Source files
SRC = waffle.cc animation.cc camera.cc rat.cc game.cc main.cc

# Output executables
OUT_LINUX = waffle.exe
OUT_WINDOWS = windows.exe

all: $(OUT_LINUX) $(OUT_WINDOWS)

$(OUT_LINUX): $(SRC)
	$(CC) -o $(OUT_LINUX) $^ $(LIBS_LINUX) $(OPT_FLAGS)

$(OUT_WINDOWS): $(SRC)
	$(CXX) -o $(OUT_WINDOWS) $^ $(CFLAGS) $(LDFLAGS) $(LIBS_WINDOWS) $(OPT_FLAGS)

.PHONY: run clean

run: $(OUT_LINUX)
	./$(OUT_LINUX)

linux: $(OUT_LINUX)

windows: $(OUT_WINDOWS)

clean:
	rm -f $(OUT_LINUX) $(OUT_WINDOWS)
