#include "Window.hpp"



void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(unsigned int width, unsigned int height, const char* windowName)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(width +GUI_WIDTH, height , windowName, NULL, NULL);
    glfwMakeContextCurrent(this->window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        // TODO: Add some assertion right here
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glViewport(0, 0, width, height);
}

void Window::mainLoop()
{
    const double updateInterval = 1.0 / FRAMES_PER_SECOND;
    auto previousUpdateTime = std::chrono::high_resolution_clock::now();
    double accumulator = 0.0;

    double fpsPreviousTime = glfwGetTime();
    this->frameCount = 0;

   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init("#version 330");

    ImFont* robotoFontBold = io.Fonts->AddFontFromFileTTF("res/font/Roboto-Bold.ttf",32.0f);
    ImFont* robotoFontRegular= io.Fonts->AddFontFromFileTTF("res/font/Roboto-Regular.ttf", 24.0f);
    
    
    while (!glfwWindowShouldClose(this->window))
    {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - previousUpdateTime;
        previousUpdateTime = currentTime;
        accumulator += elapsedTime.count();

        processEvents();

        

       
       

        while (accumulator >= updateInterval)
        {
            this->frameCount++;
            double fpsCurrentTime = glfwGetTime();
            if (fpsCurrentTime - fpsPreviousTime >= 1.0)
            {
                this->frameCount = 0;
                fpsPreviousTime = fpsCurrentTime;
            }

            this->onUpdate();
            accumulator -= updateInterval;
        }
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        this->onRender();
        

      
      
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(this->window);
        glfwPollEvents(); 
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

unsigned int Window::getCurrentFrames() const
{
    return this->frameCount;
}