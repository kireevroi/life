# GAME OF LIFE FOR *UNIX

## Description

This is a THE Game of Life made for *Unix operating system terminals

To start - compile and pipeline one of the presets for maximum fun.
```./a.out < preset.txt```

## Commands

q - quit
Space - new iteration

## Comments

Since getchar() works funky when pipelined we try to reset the stdin to TTY.
Thats why this won't correctly work on Windows.
