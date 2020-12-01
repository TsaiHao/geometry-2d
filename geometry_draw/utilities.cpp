#include <iostream>
#include <string>
#include "utilities.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

void ErrorHandler(const char* msg)
{
    std::cout << msg << std::endl;
    exit(-1);
}

void ErrorHandler(const std::string &msg)
{
    ErrorHandler(msg.c_str());
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow *initAndCreateWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Geometry-2D", NULL, NULL);
    if (window == NULL) {
        ErrorHandler("GLFW Error: create window failed");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        ErrorHandler("GLAD Error: load glad proc failed");
    }

    return window;
}
