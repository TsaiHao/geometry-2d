#include <iostream>
#include <windows.h>
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



    Shader shader("C:\\Users\\Admin\\source\\repos\\geometry-2d-master\\geometry_2d\\src\\_shaders\\vertex.vert",
                  "C:\\Users\\Admin\\source\\repos\\geometry-2d-master\\geometry_2d\\src\\_shaders\\fragment.frag");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        triangle.draw();
        triangle2.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
	return 0;
}
