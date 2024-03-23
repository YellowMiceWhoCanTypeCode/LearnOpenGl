
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>

//�Դ��ڵĻص�����������ÿ�δ��ڴ�С������ʱ����
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//��������ĺ���
void processInput(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main() 
{
    //ʵ����glfw����
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //�������ڶ���
    auto* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == nullptr) {
        std::cout << "create window failed";
        glfwTerminate();
        return -1;
    }

    //֪ͨGLFW����������������Ϊ��ǰ�߳���������
    glfwMakeContextCurrent(window);

    //GLAD����������OpenGL�ĺ���ָ��ģ�����ڵ����κ�OpenGL�ĺ���ǰ����ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //�����ӿڵ�λ�úʹ�С
    glViewport(0, 0, 800, 600);

    //ע�ắ��������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //�����Զ���Shader��Ķ���
    Shader ourShader("shader.vs.txt", "shader.fs.txt");

    /*
    //����������ɫ������ʹ��ID������
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //��������ɫ��Դ�븽�ӵ���ɫ�������ϣ�Ȼ�������ɫ��
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //��鶥����ɫ���Ƿ����ɹ�
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error::Shader::Vertex::Compilation_Failed\n" << infoLog << std::endl;
    }


    //����Ƭ����ɫ��,��Ƭ����ɫ��Դ�븽�ӵ�Ƭ����ɫ�������ϣ�������Ƭ����ɫ��
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //���Ƭ����ɫ���Ƿ����ɹ�
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout<< "Error::Shader::Fragment::Compilation_Failed\n" << infoLog << std::endl;
    }


    //������ɫ���������
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    //����ɫ�����ӵ����������,Ȼ������
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //���������ɫ���Ƿ�ɹ�
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error::Shader::Paogram::Compilation_Failed\n" << infoLog << std::endl;
    }

    //����������
    glUseProgram(shaderProgram);
    //ɾ����ɫ������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    */

    //���������ζ�������
    float vertices[] = {
        // positions         // colors
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top 
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    //��Ҫ���ƵĶ�������
    unsigned int indices[] = {
        0,1,3,
        //1,2,3
    };

    //���ɶ��㻺�����
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //�󶨶����������
    glBindVertexArray(VAO);

    //�����㻺�����󶨵����㻺��������
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //���ƶ������ݵ������ڴ���
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //��EBO�������������ݸ��Ƶ��������ڴ���
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //λ������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //��ɫ����
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    

    //��Ⱦѭ��
    //ÿ��ѭ����ʼǰ�����GLFW�Ƿ�Ҫ���˳�
    while (!glfwWindowShouldClose(window))
    {
        //����Ƿ�����escape��
        processInput(window);

        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        //�趨ʹ��ָ������ɫ��������󣬲��󶨵�VAO
        ourShader.use();
        float timeValue = glfwGetTime();
        timeValue /= 5;
        if (timeValue > 0.5) {
            timeValue = timeValue - 0.5;
        }
        ourShader.setFloat("vertexOffset", timeValue);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //����Ƿ��д����¼����������룬����ƶ��ȣ�
        glfwPollEvents();

        //������ɫ����
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    //ɾ�������������Դ
    glfwTerminate();
    return 0;
}