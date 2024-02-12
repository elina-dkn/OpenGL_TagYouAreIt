#include "Mesh.h"
#include "Shader.h"

Mesh::Mesh() {
    m_shader = nullptr;
    m_vertexBuffer = 0;
    m_colorBuffer = 0;
    for (int i = 0; i < 10; i++) {
        m_npc_world.push_back(glm::mat4(1.0f));
    }
    player_position = glm::vec4(1.0f);

    m_player_world = glm::mat4(1.0f);
    for (int i = 0; i < 10; i++) {
        npc_position.push_back(glm::vec4(1.0f));
    }

    playerSpeed = 0.01f;
    npcSpeed = 0.003f;
}
Mesh::~Mesh() {}

void Mesh::Create_player(Shader* _shader) {
    m_shader = _shader;

    m_vertexData = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 
        0.0f, 1.0f, 0.0f};
   
    m_colorData = {
      1.0f, 0.0f,0.0f, 0.0f,
      1.0f, 0.0f,0.0f, 0.0f,
      1.0f, 0.0f,0.0f, 0.0f
    };
        
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_colorData.size() * sizeof(float), m_colorData.data(), GL_STATIC_DRAW);
}


void Mesh::Color_update() {
    m_colorData = {
       0.0f, 0.0f,1.0f, 0.0f,
       0.0f, 0.0f,1.0f, 0.0f,
       0.0f, 0.0f,1.0f, 0.0f
    };
    glGenBuffers(1, &m_colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_colorData.size() * sizeof(float), m_colorData.data(), GL_STATIC_DRAW);
}

void Mesh::Create_npc(Shader* _shader, int a) {
    m_shader = _shader;

    m_vertexData = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f };
    m_colorData = {
       0.0f, 1.0f,0.0f, 0.0f,
       0.0f, 1.0f,0.0f, 0.0f,
       0.0f, 1.0f,0.0f, 0.0f
    };

    
    int x = rand()%20 - 10;
    int y = rand()%20 - 10;
  
    m_npc_world.at(a)[3][0] = x;
    m_npc_world.at(a)[3][1] = y;
    npc_position.at(a) = m_npc_world.at(a)[3];
    
    
  

    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_colorData.size() * sizeof(float), m_colorData.data(), GL_STATIC_DRAW);
}
void Mesh::Npc_move(int a, glm::vec3 player_p) {
    npc_position.at(a) = m_npc_world.at(a)[3];
    player_position = { player_p, 0 };

    
    
    float distance = glm::distance(player_position, npc_position.at(a));
    if (distance <= 2 ) {
        Color_update();
    }
    if (distance > 11) {
        
        glm::vec4 direction = player_position - npc_position.at(a);

        direction = glm::normalize(direction);
        
        direction = { direction.x * npcSpeed, direction.y * npcSpeed, 0.0f, 0.0f };
        
        
        glm::vec3 pos = { direction.x, direction.y, 0.0f };
        
        m_npc_world.at(a) = glm::translate(m_npc_world.at(a), pos);
        
    }
    else if (distance <= 10) {
        glm::vec4 direction = npc_position.at(a) - player_position;

        direction = glm::normalize(direction);
        
        direction = { direction.x * npcSpeed, direction.y * npcSpeed, 0.0f, 0.0f };
        glm::vec3 pos = { direction.x, direction.y, 0.0f };
        
        
        m_npc_world.at(a) = glm::translate(m_npc_world.at(a), pos);
        
    }
    
  
    
}
void Mesh::Cleanup() {
    glDeleteBuffers(1, &m_vertexBuffer);
    glDeleteBuffers(2, &m_colorBuffer);
}


void Mesh::Move_left() {
    m_player_world = glm::translate(m_player_world, { -playerSpeed,0,0});
    player_position = m_player_world[3];
}
void Mesh::Move_right() {
    m_player_world = glm::translate(m_player_world, { playerSpeed,0.0f,0.0f});
    player_position = m_player_world[3];
}
void Mesh::Move_up() {
    m_player_world = glm::translate(m_player_world, { 0,playerSpeed,0 });
    player_position = m_player_world[3];
    
}
void Mesh::Move_down() {
    m_player_world = glm::translate(m_player_world, { 0,-playerSpeed,0 });
    player_position = m_player_world[3];
    
}

void Mesh::Render_player(glm::mat4 _wvp) {
    glUseProgram(m_shader->GetProgramID());

    glEnableVertexAttribArray(m_shader->GetAttrVertices());
    glEnableVertexAttribArray(m_shader->GetAttrColors());
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(m_shader->GetAttrVertices(), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glVertexAttribPointer(m_shader->GetAttrColors(), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    
    
    
    _wvp *= m_player_world;
    
    glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(m_shader->GetAttrColors());
    glDisableVertexAttribArray(m_shader->GetAttrVertices());
}
void Mesh::Render_npc(glm::mat4 _wvp, int a) {
    glUseProgram(m_shader->GetProgramID());

    glEnableVertexAttribArray(m_shader->GetAttrVertices());
    glEnableVertexAttribArray(m_shader->GetAttrColors());
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glVertexAttribPointer(m_shader->GetAttrVertices(), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBuffer);
    glVertexAttribPointer(m_shader->GetAttrColors(), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    
    
    
    
    _wvp *= m_npc_world.at(a);


    glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(m_shader->GetAttrColors());
    glDisableVertexAttribArray(m_shader->GetAttrVertices());
}