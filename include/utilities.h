#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1000

void ErrorHandler(const char* msg);
void ErrorHandler(const std::string &msg);

// GLFW tools
GLFWwindow *initAndCreateWindow();

#endif
