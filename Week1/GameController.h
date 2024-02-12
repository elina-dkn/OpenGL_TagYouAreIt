#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardIncludes.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include<vector>

class GameController : public Singleton<GameController>
{
public:
    GameController();
    virtual ~GameController() { }

    void Initialize();
    void RunGame();

private:
    Shader m_shader;
    Mesh m_player_mesh;
    Camera m_camera;
    std::vector<Mesh> m_npc_mesh;

};

#endif //

