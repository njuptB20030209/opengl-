#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"shader.h"
#include"camera.h"
#include"Material.h"
#include"Lights.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include<iostream>
//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
#pragma region Model_Data
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};
glm::vec3 pointLightPositions[] = {
     glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
};
glm::vec3 pointLightColors[] = {
      glm::vec3(0.4f, 0.7f, 0.1f),
    glm::vec3(0.4f, 0.7f, 0.1f),
    glm::vec3(0.4f, 0.7f, 0.1f),
    glm::vec3(0.4f, 0.7f, 0.1f)
};
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



unsigned int LoadImagesToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot);
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
#pragma endregion

    #pragma region Init_Shader_Program
	Shader objectShader("object.vert", "object.frag");
	Shader lampShader("lamp.vert", "lamp.frag");
#pragma endregion

    #pragma region Init Material and Lights
    Material* myMaterial = new Material(
        LoadImagesToGPU("container2.png",GL_RGBA,GL_RGBA, Material::DIFFUSE),
        LoadImagesToGPU("lighting_maps_specular_color.png", GL_RGBA, GL_RGBA, Material::SPECULAR),
        32.0f);

    Light baseLight(glm::vec3(0.05f), glm::vec3(0.8f), glm::vec3(1.0f), glm::vec3(1.2f, 1.0f, 2.0f));
    
    DirLight directionLight(baseLight, glm::vec3(-0.2f, -1.0f, -0.3f));
    directionLight.setAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
    directionLight.setDiffuse(glm::vec3(1.0f, 1.0f, 1.0f));
    directionLight.setSpecular(glm::vec3(1.0f, 1.0f, 1.0f));
    
    SpotLight spotLight(baseLight, camera.Front, glm::vec3(1.0f, 0.07f, 0.017f), glm::cos(glm::radians(7.0f)), glm::cos(glm::radians(10.0f)));
    spotLight.setPos(camera.Position);
    spotLight.setAmbient(glm::vec3(0.0f, 0.0f, 0.0f));
    spotLight.setDiffuse(glm::vec3(0.0f, 1.0f, 0.0f));
    spotLight.setSpecular(glm::vec3(0.0f, 1.0f, 0.0f));
    
    PointLight pointLights[4];
    for (int i = 0; i < 4; i++)
    {
        pointLights[i].setPos(pointLightPositions[i]);
        glm::vec3 ambientColor = glm::vec3(pointLightColors[i].x*0.1, pointLightColors[i].y * 0.1, pointLightColors[i].z * 0.1);
        pointLights[i].setAmbient(ambientColor);
        pointLights[i].setDiffuse(pointLightColors[i]);
        pointLights[i].setDiffuse(pointLightColors[i]);

    }

#pragma endregion

    #pragma region Init and Load Models to VAO,VBO
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //second,configure the light's VAO
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
#pragma endregion

    #pragma region Init and Load Textures
   /*unsigned int emissionMap;
   emissionMap = LoadImagesToGPU("matrix.jpg",GL_RGB,GL_RGB,2);*/
#pragma endregion

    #pragma region Prepare MVP matrixs
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
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
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //set material -> shader program
        objectShader.use();
        //set material -> textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, myMaterial->specular);
       /* glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, myMaterial->emissionMap);*/

        //set material -> uniforms
        objectShader.setVec3("viewPos", camera.Position);

        //set direction light
        objectShader.setVec3("dirLight.direction", directionLight.direction);
        objectShader.setVec3("dirLight.ambient", directionLight.ambient);
        objectShader.setVec3("dirLight.diffuse", directionLight.diffuse); // 将光照调暗了一些以搭配场景
        objectShader.setVec3("dirLight.specular",directionLight.specular);
      //  objectShader.setVec3("light.color", directionLight.color);

        //set pointLights
        std::string s_position = "pointLights[x].position";
        std::string s_ambient = "pointLights[x].ambient";
        std::string s_diffuse = "pointLights[x].diffuse";
        std::string s_specular = "pointLights[x].specular";
        std::string s_constant = "pointLights[x].constant";
        std::string s_linear = "pointLights[x].linear";
        std::string s_quadratic = "pointLights[x].quadratic";
        for (int i = 0; i < 4; i++)
        {
            char index = i + '0';
            s_position[12] =index;
            s_ambient[12] = index;
            s_diffuse[12] = index;
            s_specular[12] = index;
            s_constant[12] = index;
            s_linear[12] = index;
            s_quadratic[12] = index;

            objectShader.setVec3(s_position, pointLights[i].position);
            objectShader.setVec3(s_ambient, pointLights[i].ambient);
            objectShader.setVec3(s_diffuse, pointLights[i].diffuse); // 将光照调暗了一些以搭配场景
            objectShader.setVec3(s_specular, pointLights[i].specular);
            objectShader.setFloat(s_constant, pointLights[i].attenuation.x);
            objectShader.setFloat(s_linear, pointLights[i].attenuation.y);
            objectShader.setFloat(s_quadratic, pointLights[i].attenuation.z);
            // objectShader.setVec3("light.color", pointLights[i].color);
        }
        //set spotLight
        objectShader.setVec3("spotLight.position", spotLight.position);
        objectShader.setVec3("spotLight.direction", camera.Front);
        objectShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        objectShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f); // 将光照调暗了一些以搭配场景
        objectShader.setVec3("spotLight.specular", spotLight.specular);
        objectShader.setFloat("spotLight.constant", spotLight.attenuation.x);
        objectShader.setFloat("spotLight.linear", spotLight.attenuation.y);
        objectShader.setFloat("spotLight.quadratic", spotLight.attenuation.z);
        objectShader.setFloat("spotLight.cutOff", spotLight.cutOff);
        objectShader.setFloat("spotLight.outerCutOff", spotLight.outerCutOff);
       
        // objectShader.setVec3("spotLight.color", spotLight.color);

        //set matierial
        objectShader.setInt("material.diffuse",Material::DIFFUSE);
        objectShader.setInt("material.specular", Material::SPECULAR);
      //  objectShader.setInt("material.emissionMap", Material::EMISSIONMAP);
        objectShader.setFloat("material.shininess", myMaterial->shininess);

        //set MVP
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = camera.GetViewMatrix();
        objectShader.setMat4("projection", projection);
        objectShader.setMat4("view", view);
        //set model
        glBindVertexArray(cubeVAO);
        //drawcall
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            objectShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //set lamp uniforms and rend lamps
        lampShader.use();
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
       
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLights[i].position);
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
            lampShader.setMat4("model", model);
            lampShader.setVec3("lightColor", pointLights[i].diffuse);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //swap buffers and prepare for next frame
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    //clear all resources
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
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
unsigned int LoadImagesToGPU(const char* filename,GLint internalFormat,GLenum format,int textureSlot)
{
    unsigned int TexBuffer;
    glGenTextures(1, &TexBuffer);
    glActiveTexture(GL_TEXTURE0+textureSlot);
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
