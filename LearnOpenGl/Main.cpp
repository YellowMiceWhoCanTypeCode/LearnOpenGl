
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>

//对窗口的回调函数，会在每次窗口大小被调整时调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//处理输入的函数
void processInput(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


int main() 
{
    //实例化glfw窗口
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //创建窗口对象
    auto* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == nullptr) {
        std::cout << "create window failed";
        glfwTerminate();
        return -1;
    }

    //通知GLFW将窗口上下文设置为当前线程主上下文
    glfwMakeContextCurrent(window);

    //GLAD是用来管理OpenGL的函数指针的，因此在调用任何OpenGL的函数前，初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //设置视口的位置和大小
    glViewport(0, 0, 800, 600);

    //注册函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //创建自定义Shader类的对象
    Shader ourShader("shader.vs.txt", "shader.fs.txt");

    /*
    //创建顶点着色器对象，使用ID来引用
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //将顶点着色器源码附加到着色器对象上，然后编译着色器
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //检查顶点着色器是否编译成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error::Shader::Vertex::Compilation_Failed\n" << infoLog << std::endl;
    }


    //创建片段着色器,将片段着色器源码附加到片段着色器对象上，并编译片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //检查片段着色器是否编译成功
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout<< "Error::Shader::Fragment::Compilation_Failed\n" << infoLog << std::endl;
    }


    //创建着色器程序对象
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    //将着色器附加到程序对象上,然后链接
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //检查链接着色器是否成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error::Shader::Paogram::Compilation_Failed\n" << infoLog << std::endl;
    }

    //激活程序对象
    glUseProgram(shaderProgram);
    //删除着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    */

    //定义三角形顶点数据
    float vertices[] = {
        // positions         // colors
         0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
        -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top 
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    //需要绘制的顶点索引
    unsigned int indices[] = {
        0,1,3,
        //1,2,3
    };

    //生成顶点缓冲对象
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //绑定顶点数组对象
    glBindVertexArray(VAO);

    //将顶点缓冲对象绑定到顶点缓冲类型上
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //复制顶点数据到缓冲内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //绑定EBO，并将索引数据复制到缓冲区内存上
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    //位置属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //颜色属性
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    

    //渲染循环
    //每次循环开始前，检查GLFW是否要求被退出
    while (!glfwWindowShouldClose(window))
    {
        //检测是否按下了escape键
        processInput(window);

        glClearColor(0.2, 0.3, 0.3, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        //设定使用指定的着色器程序对象，并绑定到VAO
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

        //检查是否有触发事件（键盘输入，鼠标移动等）
        glfwPollEvents();

        //交换颜色缓冲
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    //删除分配的所有资源
    glfwTerminate();
    return 0;
}