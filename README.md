# m4w-render
My testing around with 3D OpenGL rendering

The goal of this project is to be an OpenGL Game Library. Including light, shadows, collisions and other game things.

## Compilation
I started this project before I knew about special compilers like Cmake. So I wrote my own Python script, which only compiles Files that have changed.
An example of how to compile would be:
```bash
python3 .vscode/custom_build/build.py \
        src \
        .vscode/custom_build/debug \
        unix-debug \
        True \
        /usr/bin/g++ \
        -std=c++2a -g -lglfw -lGLEW -lGL -D M4W_DEBUG
```
Where the arguments are:
```yaml
Source Folder: src
Temp Folder: .vscode/custom_build/debug \
Output File: unix-debug \
Change only: True \
Compiler Path: /usr/bin/g++ \
Compiler args: -std=c++2a -g -lglfw -lGLEW -lGL -D M4W_DEBUG
```

To compile you need glfw and glew libraries.
