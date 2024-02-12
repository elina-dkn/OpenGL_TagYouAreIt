#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
class Shader;

class Mesh
{
public:
    Mesh();
    virtual ~Mesh();


    void Create_player(Shader* _shader);
    void Create_npc(Shader* _shader, int a);
    void Cleanup();
    void Render_player(glm::mat4 _wvp);
    void Render_npc(glm::mat4 _wvp, int a);
    void Npc_move(int a, glm::vec3 p);
    void Move_left();
    void Move_right();
    void Move_up();
    void Move_down();
    void Color_update();
    glm::vec3 Get_player_position() { return player_position; }
private:
    Shader* m_shader;
    GLuint m_vertexBuffer;
    GLuint m_colorBuffer;
    std::vector<GLfloat> m_vertexData;
    std::vector<GLfloat> m_colorData;
    glm::mat4 m_player_world;
    glm::vec4 player_position;
    std::vector<glm::vec4> npc_position;
    std::vector<glm::mat4> m_npc_world;
    float playerSpeed;
    float npcSpeed;
};

#endif

