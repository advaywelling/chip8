CXX = clang++
FLAGS = -std=c++17 -Wall $(shell sdl2-config --cflags)
LIBS = $(shell sdl2-config --libs)
TARGET = chip8
OBJS = main.o chip8.o display.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.cc chip8.h display.h
	$(CXX) $(FLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)