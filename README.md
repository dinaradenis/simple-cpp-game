# The Moonlit Ruins

A small command-line "choose your own adventure" game written in C++.

## Build

With `g++`:

```text
g++ -std=c++17 -Wall -Wextra -pedantic adventure.cpp -o adventure
```

On Windows with MinGW, run the resulting program with:

```text
adventure.exe
```

The game includes branching paths, health, inventory, multiple endings, and a
play-again loop.
