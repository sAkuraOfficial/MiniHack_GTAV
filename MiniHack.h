#pragma once
#include "hello_imgui/hello_imgui.h"
struct hackStatus
{
    // player
    bool player_god = false;
    bool player_noClip = false;
    bool player_noWanted = false;
    // vehicle
    bool vehicle_god = false;
};
class MiniHack
{
  private:
    HelloImGui::RunnerParams p;

  public:
    MiniHack();
    ~MiniHack();
    void Run();
    static void CreateFont();
    static void CreateGUI();
};

