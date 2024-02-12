#include "GameController.h"
#include "WindowController.h"


GameController::GameController() {
    m_shader = { };
    m_player_mesh = { };
    m_npc_mesh = {};
    m_camera = { }; 

}

void GameController::Initialize() {
    GLFWwindow* window = WindowController::GetInstance().GetWindow();
    M_ASSERT(glewInit() == GLEW_OK, "Failed to initialze GLEW");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_CULL_FACE);

    m_camera = Camera(WindowController::GetInstance().GetResolution());
    
}

void GameController::RunGame() {
    


    m_shader = Shader();
    m_shader.LoadShaders("SimpleVertexShader.vertexshader.txt", "SimpleFragmentShader.fragmentshader.txt");
    m_player_mesh = Mesh();
    m_player_mesh.Create_player(&m_shader);

    for (int i = 0; i < 10; i++) {
        Mesh a = Mesh();
        a.Create_npc(&m_shader, i);
        m_npc_mesh.push_back(a);
    }
    

    GLFWwindow* win = WindowController::GetInstance().GetWindow();
    do {
       
        if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) {
            m_player_mesh.Move_left();
        }
        else if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) {
            m_player_mesh.Move_right();
        }
        else if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) {
            m_player_mesh.Move_up();
        }
        else if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) {
            m_player_mesh.Move_down();
        }

        glClear(GL_COLOR_BUFFER_BIT);

        
        for (int i = 0; i < 10; i++) {
            
            m_npc_mesh.at(i).Npc_move(i, m_player_mesh.Get_player_position());
            m_npc_mesh.at(i).Render_npc(m_camera.GetProjection() * m_camera.GetView(), i);;
            
        }

        m_player_mesh.Render_player(m_camera.GetProjection() * m_camera.GetView());
        
        glfwSwapBuffers(win);
        glfwPollEvents();
    } while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(win) == 0);

    m_player_mesh.Cleanup();
    for (int i = 0; i < 10; i++) {
        m_npc_mesh.at(i).Cleanup();
    }
    m_shader.Cleanup();
}

