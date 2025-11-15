#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//#include "MyThread.h"

#define LOG(X) std::cout << X << std::endl

int main()
{
    /* Run Thread for Create Random Static float*/
    // std::thread MyWorker(DoWork);

    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "JRender", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        LOG("You have Error");

    LOG(glGetString(GL_VERSION));

    float mypositions[6] = { -0.5f,-0.5f,0.5f,0.5f,0.5f,-0.5f};

    unsigned int Mybuffer;
    glGenBuffers(1, &Mybuffer);
    glBindBuffer(GL_ARRAY_BUFFER, Mybuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mypositions) , mypositions , GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    //glVertexAttribpointer(0,2 ,GL_FLOAT , GL_FALSE , sizeof(float)*2 , 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // DrawTriangle
        glDrawArrays(GL_TRIANGLES , 0 , 3);
        //glDrawElements(GL_TRIANGLES)

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}