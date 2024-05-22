#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Eigen/Dense>
#include <SFML/System/Vector2.h>

// Function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int windowWidth = 800;
int windowHeight = 600;

bool isMouseHeld = false;


struct physicsObject
{
    sf::vector2 position_current;
    sf::vector2 position_old;
    sf::vector2 acceleration;

    void updatePosition(float dt) {
        const std::vector<double> velocity = position_current - position_old;
        position_old = position_current;
        position_current = position_current + velocity + acceleration * dt * dt;
    }
}


void verlet()
{

}


void physics()
{

}


void render()
{
    // Pixel coordinates for the square
    int squareSize = 100;
    int x = 350; // X position in pixels
    int y = 250; // Y position in pixels

    // Convert pixel coordinates to normalized device coordinates
    float left = 2.0f * x / windowWidth - 1.0f;
    float right = 2.0f * (x + squareSize) / windowWidth - 1.0f;
    float top = 1.0f - 2.0f * y / windowHeight;
    float bottom = 1.0f - 2.0f * (y + squareSize) / windowHeight;

    glBegin(GL_POLYGON);
        glVertex2f(left, top);
        glVertex2f(right, top);
        glVertex2f(right, bottom);
        glVertex2f(left, bottom);
    glEnd();
}


double xpos, ypos;
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    ::xpos = xpos;
    ::ypos = ypos;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        isMouseHeld = true;
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        isMouseHeld = false;
}


int main()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For MacOS
    #endif

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "GLFW OpenGL Game", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(0, 0, windowWidth, windowHeight);

    // Callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        // Debug checks
        // std::cout << "Cursor Position: (" << xpos << ", " << ypos << ")" << std::endl;
        // std::cout << "isMouseHeld: " << isMouseHeld << std::endl;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}


// Function to process input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


// Callback function to adjust the viewport size when the window size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
