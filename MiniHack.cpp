#include "MiniHack.h"

MiniHack::MiniHack()
{
    p.appWindowParams.windowGeometry.size = {100, 300};
    p.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::ProvideFullScreenWindow;
    p.imGuiWindowParams.rememberStatusBarSettings = false;
    p.imGuiWindowParams.rememberTheme = false;
    p.rememberSelectedAlternativeLayout = false;
    p.callbacks.ShowGui = CreateGUI;
    p.callbacks.LoadAdditionalFonts = CreateFont;
}

MiniHack::~MiniHack()
{
}

void MiniHack::Run()
{
    HelloImGui::Run(p);
}

void MiniHack::CreateFont()
{
    HelloImGui::LoadFontDpiResponsive("fonts/seguiemj-1.45-3d.ttf", 15, {});
}

void MiniHack::CreateGUI()
{
    static hackStatus status = {};
    std::string title = "A mini hack for GTAV.";
    std::string title_f5 = "F5.TP to Way Point";
    std::string title_f6 = "F6.TP to Objective Point";
    ImGui::StyleColorsDark();
    ImGui::SetCursorPos({(ImGui::GetWindowSize().x - ImGui::CalcTextSize(title.c_str()).x) / 2, 5});
    ImGui::Text("%s", title.c_str());
    ImGui::Checkbox("player.god", &status.player_god);
    ImGui::Checkbox("player.noClip", &status.player_noClip);
    ImGui::Checkbox("player.noWanted", &status.player_noWanted);
    ImGui::Checkbox("vehicle.god", &status.vehicle_god);



    //底部的信息
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(title_f5.c_str()).x) / 2);
    ImGui::SetCursorPosY(ImGui::GetWindowSize().y - ImGui::CalcTextSize(title_f5.c_str()).y*2-10);
    ImGui::Text("%s", title_f5.c_str());
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(title_f6.c_str()).x) / 2);
    ImGui::Text("%s", title_f6.c_str());

}
