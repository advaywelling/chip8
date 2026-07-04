# Chip-8 Emulator

A Chip-8 emulator written in C++ with SDL2 for graphics and input. Loads and runs all Chip-8 ROMs (hopefully).

## About

Chip-8 is an interpreted virtual machine from the 1970s, designed to make simple games easier to program on early microcomputers. This project implements a full Chip-8 interpreter: it reads a ROM, then runs its bytecode through a fetch–decode–execute cycle, emulating the CPU, memory, display, timers, and keypad.

## Features

- Full instruction set - all 35 Chip-8 opcodes
- 64×32 monochrome display, rendered and scaled up via SDL2
- 16-key hex keypad input mapped to the keyboard
- Delay and sound timers running at 60 Hz
- Loads any standard Chip-8 ROM

## Requirements

- A C++17 compiler (clang++ or g++)
- SDL2
- make

On macOS, install SDL2 with Homebrew:

```
brew install sdl2
```

On Linux:

```
sudo apt install libsdl2-dev
```

## Usage

Run with a path to a ROM. By default the program loads a ROM from the `ROMS/` folder — edit the path in `main.cc`, or adjust it to take the ROM as a command-line argument.

The ROMS I used to test this with (and many, many more) can be found here - https://github.com/kripod/chip8-roms/tree/master 

## Controls

The Chip-8 keypad is mapped to the left side of the keyboard:

```
Chip-8 Keypad        Keyboard
1 2 3 C              1 2 3 4
4 5 6 D      -->     Q W E R
7 8 9 E              A S D F
A 0 B F              Z X C V
```

Controls vary by game. For example, Pong uses `1`/`Q` for the left paddle and `4`/`R` for the right.