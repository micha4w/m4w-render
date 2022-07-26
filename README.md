# m4w-render
My testing around with 3D OpenGL rendering

The goal of this project is to be an OpenGL Game Library. Including light, shadows, collisions and other game things.

## Compilation
To compile you need stb, glm, glfw3 and glew, then run:
```bash
g++ $(find src -name *.cpp -type f) $(find src -type d | awk '{print "-I"$1}') -lglfw -lGLEW -lGL -DM4W_RELEASE -std=c++2a -o out
```
This will create an executable called out file.
