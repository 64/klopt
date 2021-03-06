# klopt - Keyboard Layout Optimiser

Computes the most optimal keyboard layout for a given piece of text using simulated annealing.

This project is a work in progress - the model only tracks finger distance and only supports British keyboard layouts, but I hope to change this in future.

Licensed under GPLv3.

## Compiling

Install submodules with `git submodule update --init`. Then use the `cmake` generator of your choice, with a C++20-compatible compiler (for ranges and concepts support).
