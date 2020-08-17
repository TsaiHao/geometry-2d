#include <iostream>
#include <string>
#include <fstream>
#include "glad/glad.h"
#include "GLUtility.h"
#include "utilities.h"
#include "GLFW/glfw3.h"
#include "shape.h"

int main()
{
    glfwInit();
    std::cout << "Program initializing " << std::endl;
    auto window = initAndCreateWindow();

    geometry_2d::Triangle triangle(0.0f, 0.1f, -0.1f, -0.1f, 0.1f, -0.1f),
            triangle2(-0.5f, -0.3f, -0.4f, 0.0f, -0.2f, -0.5f);
    geometry_2d::Rectangle rec(0.1f, 0.9f, 0.9f, 0.1f);
    geometry_2d::Circle circle(0.5f, -0.75f, 0.2f);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        triangle.draw();
        triangle2.draw();
        rec.draw();
        circle.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
	return 0;
}
