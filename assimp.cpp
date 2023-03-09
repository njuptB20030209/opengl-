#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"shader.h"
#include"camera.h"
#include"Material.h"
#include"Lights.h"
#include"Mesh.h"
#include"Model.h"

#include<iostream>
//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
#pragma region Model_Data

#pragma endregion
#pragma region Camera_Declare
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
#pragma endregion
#pragma region Input_Declare
float lastX = SCR_WIDTH / 2;
float lastY = SCR_HEIGHT / 2;
bool firstMouse = true;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
#pragma endregion

//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
#pragma region Open_a_Window
    //glfw:initialize and configure
    glfwInit();
    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "opengl", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFWwindow" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    //mouse's cursor is hidden
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //glad: load all opengl function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "failed to initialize glad" << std::endl;
        return -1;
    }

    //configure global opengl set
    glEnable(GL_DEPTH_TEST);
    stbi_set_flip_vertically_on_load(true);
#pragma endregion

#pragma region Init_Shader_Program
    Shader myShader("assimpMaps.vert", "assimpMaps.frag");
#pragma endregion

#pragma region Init Material and Lights
    Light baseLight(glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.0f), glm::vec3(1.2f, 1.0f, 2.0f));

    DirLight directionLight(baseLight, glm::vec3(-0.2f, -1.0f, -0.3f));
    directionLight.setAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
    directionLight.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
    directionLight.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

    SpotLight spotLight(baseLight, camera.Front, glm::vec3(1.0f, 0.07f, 0.017f), glm::cos(glm::radians(7.0f)), glm::cos(glm::radians(10.0f)));
    spotLight.setPos(camera.Position);
    spotLight.setAmbient(glm::vec3(0.0f, 0.0f, 0.0f));
    spotLight.setDiffuse(glm::vec3(0.8f, 0.8f, 0.8f));
    spotLight.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

    PointLight pointLight(baseLight,glm::vec3(1.0f,0.09f,0.032f));

   
#pragma endregion

#pragma region Init and Load Models to VAO,VBO
   
    Model myModel("D:/c++/opengl/OpenGLHomeWork/x64/Debug/model/nanosuit.obj");

    
#pragma endregion

#pragma region Init and Load Textures

#pragma endregion

#pragma region Prepare MVP matrixs
    
#pragma endregion
    while (!glfwWindowShouldClose(window))
    {
        //deltaTime
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //process input
        processInput(window);

        //clear screen
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.use();
        
        //set MVP
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        myShader.setMat4("projection", projection);
        myShader.setMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	
        myShader.setMat4("model", model);
        //set uniform
        myShader.setVec3("viewPos", camera.Position);

        //set direction light
        myShader.setVec3("dirLight.direction", directionLight.direction);
        myShader.setVec3("dirLight.ambient", directionLight.ambient);
        myShader.setVec3("dirLight.diffuse", directionLight.diffuse); // 将光照调暗了一些以搭配场景
        myShader.setVec3("dirLight.specular", directionLight.specular);
        //  myShader.setVec3("light.color", directionLight.color);

        //set pointLights
        myShader.setVec3("pointLight.position", pointLight.position);
        myShader.setVec3("pointLight.ambient", pointLight.ambient);
        myShader.setVec3("pointLight.diffuse", pointLight.diffuse); // 将光照调暗了一些以搭配场景
        myShader.setVec3("pointLight.specular", pointLight.specular);
        myShader.setFloat("pointLight.constant", pointLight.attenuation.x);
        myShader.setFloat("pointLight.linear", pointLight.attenuation.y);
        myShader.setFloat("pointLight.quadratic", pointLight.attenuation.z);
           
        myShader.setVec3("spotLight.position", spotLight.position);
        myShader.setVec3("spotLight.direction", camera.Front);
        myShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        myShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f); // 将光照调暗了一些以搭配场景
        myShader.setVec3("spotLight.specular", spotLight.specular);
        myShader.setFloat("spotLight.constant", spotLight.attenuation.x);
        myShader.setFloat("spotLight.linear", spotLight.attenuation.y);
        myShader.setFloat("spotLight.quadratic", spotLight.attenuation.z);
        myShader.setFloat("spotLight.cutOff", spotLight.cutOff);
        myShader.setFloat("spotLight.outerCutOff", spotLight.outerCutOff);

        //drawcall
        myModel.Draw(myShader);
        //swap buffers and prepare for next frame
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = -(ypos - lastY);

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}
unsigned int LoadImagesToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot)
{
    unsigned int TexBuffer;
    glGenTextures(1, &TexBuffer);
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, TexBuffer);
    int width, height, nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannel, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "load image failed" << std::endl;
    }
    stbi_image_free(data);
    return TexBuffer;
}
