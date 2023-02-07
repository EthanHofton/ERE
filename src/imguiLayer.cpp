#include <ere/core/imguiLayer.hpp>
#include <ere/mappings/keyMap.hpp>
#include <ere/core/imgui_impl_glfw.hpp>
#include <ere/core/imgui_impl_opengl3.hpp>
#include <ereConfig.hpp>
#include <imgui.h>
#include <ere/core/logger.hpp>

namespace ere {

void imguiLayer::begin(const double& t_delta, const glm::vec2& t_winSize, const glm::vec2& t_framebuffSize) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(t_winSize.x, t_winSize.y);
    io.DisplayFramebufferScale = ImVec2(t_framebuffSize.x / t_winSize.x, t_framebuffSize.y / t_winSize.y);
    io.DeltaTime = t_delta;

    #ifdef USE_OPENGL
    ImGui_ImplOpenGL3_NewFrame();
    #endif 
    ImGui::NewFrame();
}
void imguiLayer::end() {
    ImGui::Render();
    #ifdef USE_OPENGL
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    #endif
}

bool imguiLayer::onAttach(attachEvent& t_e) {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.KeyMap[ImGuiKey_Tab]        = ERE_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow]  = ERE_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = ERE_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow]    = ERE_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow]  = ERE_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp]     = ERE_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown]   = ERE_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home]       = ERE_KEY_HOME;
    io.KeyMap[ImGuiKey_End]        = ERE_KEY_END;
    io.KeyMap[ImGuiKey_Insert]     = ERE_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete]     = ERE_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace]  = ERE_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space]      = ERE_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter]      = ERE_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape]     = ERE_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A]          = ERE_KEY_A;
    io.KeyMap[ImGuiKey_C]          = ERE_KEY_C;
    io.KeyMap[ImGuiKey_V]          = ERE_KEY_V;
    io.KeyMap[ImGuiKey_X]          = ERE_KEY_X;
    io.KeyMap[ImGuiKey_Y]          = ERE_KEY_Y;
    io.KeyMap[ImGuiKey_Z]          = ERE_KEY_Z;

    #ifdef USE_OPENGL
    ImGui_ImplOpenGL3_Init("#version 410");
    #endif

    return false;
}
bool imguiLayer::onDetach(detachEvent& t_e) {
    #ifdef USE_OPENGL
    ImGui_ImplOpenGL3_Shutdown();
    #endif
    ImGui::DestroyContext();
    return false;
}

bool imguiLayer::onKeyPressed(keyPressedEvent& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.KeysDown[t_e.getKeyCode()] = true;

    io.KeyCtrl  = io.KeysDown[ERE_KEY_LEFT_CONTROL] || io.KeysDown[ERE_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[ERE_KEY_LEFT_SHIFT]   || io.KeysDown[ERE_KEY_RIGHT_SHIFT];
    io.KeyAlt   = io.KeysDown[ERE_KEY_LEFT_ALT]     || io.KeysDown[ERE_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[ERE_KEY_LEFT_SUPER]   || io.KeysDown[ERE_KEY_RIGHT_SUPER];
    return false;
}

bool imguiLayer::onKeyReleased(keyReleasedEvent& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.KeysDown[t_e.getKeyCode()] = false;
    return false;
}
bool imguiLayer::onKeyTyped(keyTypedEvent& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    int keycode = t_e.getKeyCode();
    if (keycode > 0 && keycode < 0x10000) {
        io.AddInputCharacter((unsigned short)keycode);
    }
    return false;
}
bool imguiLayer::onMouseButtonPressed(mouseButtonPressedEvent& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.MouseDown[t_e.getMouseButton()] = true;
    return false;
}
bool imguiLayer::onMouseButtonReleased(mouseButtonReleasedEvent& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.MouseDown[t_e.getMouseButton()] = false;
    return false;
}
bool imguiLayer::onMouseMoved(mouseMovedEvent& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos = ImVec2(t_e.getPos().x, t_e.getPos().y);
    return false;
}
bool imguiLayer::onMouseScrolled(mouseScrolledEvent& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.MouseWheel  += t_e.getOffset().y;
    io.MouseWheelH += t_e.getOffset().x;
    return false;
}
bool imguiLayer::onWindowResize(windowResizeEvent& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2(t_e.getWindowSize().x, t_e.getWindowSize().y);
    return false;
}

bool imguiLayer::onWindowFramebufferResize(windowFramebufferResizeEvent &t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.DisplayFramebufferScale = ImVec2(t_e.getWindowFramebufferSize().x / io.DisplaySize.x, t_e.getWindowFramebufferSize().y / io.DisplaySize.y);
    return false;
}

}

