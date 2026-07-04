CXX = clang++
FLAGS = -std=c++17 -Wall -Iinclude $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs)
TARGET = chip8
OBJS = src/main.o src/chip8.o src/display.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(TARGET) $(LIBS)

src/%.o: src/%.cc include/chip8.h include/display.h
	$(CXX) $(FLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)