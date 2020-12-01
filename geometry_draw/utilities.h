#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 800

void ErrorHandler(const char* msg);
void ErrorHandler(const std::string &msg);

// GLFW tools
GLFWwindow *initAndCreateWindow();

namespace geometry_2d {
	namespace color {
		struct color_rgba
		{
			// rgba range from 0 to 1.0
			float r;
			float g;
			float b;
			float a;
		};
	}
}

#endif
