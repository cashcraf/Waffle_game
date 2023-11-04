# Compiler and flags
CC = g++
CXX = x86_64-w64-mingw32-g++
CFLAGS = -Wall
LDFLAGS = -I/home/cashcraf/raylib/src/windows -L/home/cashcraf/raylib/src/windows
LDFLAGSweb = -I/home/cashcraf/raylib/src -I/home/cashcraf/emsdk/upstream/emscripten/system/include/emscripten -L/home/cashcraf/raylib/src
LIBS_LINUX = -lraylib -lGL -lpthread -ldl -lrt -lX11 -lm
LIBS_WINDOWS = -lraylib -lopengl32 -lgdi32 -lwinmm -lpthread
LIBS_WEB = -lraylib -lm
OPT_FLAGS = -O1  # Adjust optimization level as needed

# Emscripten tools and flags
EMCC = emcc
EMFLAGS = -O1

# Source files
SRC = waffle.cc animation.cc camera.cc rat.cc game.cc main.cc

# Output executables
OUT_LINUX = waffle.exe
OUT_WINDOWS = windows.exe
OUT_HTML = waffleWeb.html

all: $(OUT_LINUX) $(OUT_WINDOWS)

$(OUT_LINUX): $(SRC)
	$(CC) -o $(OUT_LINUX) $^ $(LIBS_LINUX) $(OPT_FLAGS)

$(OUT_WINDOWS): $(SRC)
	$(CXX) -o $(OUT_WINDOWS) $^ $(CFLAGS) $(LDFLAGS) $(LIBS_WINDOWS) $(OPT_FLAGS)

web: $(OUT_HTML)

$(OUT_HTML): $(SRC)
	$(EMCC) $(EMFLAGS) $^ -o $(OUT_HTML) $(LIBS_LINUX) $(LDFLAGSweb) -DPLATFORM_WEB -s USE_GLFW=3 -s USE_WEBGL2=1 --preload-file Sounds --preload-file Images --preload-file Headers -s ASYNCIFY --shell-file /home/cashcraf/raylib/src/shell.html

.PHONY: run clean

run: $(OUT_LINUX)
	./$(OUT_LINUX)

linux: $(OUT_LINUX)

windows: $(OUT_WINDOWS)

clean:
	rm -f $(OUT_LINUX) $(OUT_WINDOWS) $(OUT_HTML)
