#include <ere/imgui/imgui_impl_opengl3.hpp>
#include <ere/imgui/imgui_layer.hpp>
#include <ere/mappings/key_map.hpp>
#include <ere/mappings/mouse_map.hpp>
#include <imgui.h>


namespace ere {

void imgui_layer::begin(const double& t_delta, const glm::vec2& t_window_size, const glm::vec2& t_framebuff_size) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(t_window_size.x, t_window_size.y);
    io.DisplayFramebufferScale = ImVec2(t_framebuff_size.x / t_window_size.x, t_framebuff_size.y / t_window_size.y);
    io.DeltaTime = t_delta;

    #ifdef USE_OPENGL
    ImGui_ImplOpenGL3_NewFrame();
    #endif
    ImGui::NewFrame();
}
void imgui_layer::end() {
    ImGui::Render();
    #ifdef USE_OPENGL
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    #endif
}

bool imgui_layer::on_attach(attach_event& t_e) {
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
    ImGui_ImplOpenGL3_Init("#version 330");
    #endif

    return false;
}

bool imgui_layer::on_detach(detach_event& t_e) {
    #ifdef USE_OPENGL
    ImGui_ImplOpenGL3_Shutdown();
    #endif
    ImGui::DestroyContext();
    return false;
}

bool imgui_layer::on_key_pressed(key_pressed_event& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.KeysDown[t_e.get_key_code()] = true;

    io.KeyCtrl  = io.KeysDown[ERE_KEY_LEFT_CONTROL] || io.KeysDown[ERE_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[ERE_KEY_LEFT_SHIFT]   || io.KeysDown[ERE_KEY_RIGHT_SHIFT];
    io.KeyAlt   = io.KeysDown[ERE_KEY_LEFT_ALT]     || io.KeysDown[ERE_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[ERE_KEY_LEFT_SUPER]   || io.KeysDown[ERE_KEY_RIGHT_SUPER];
    return false;
}

bool imgui_layer::on_key_released(key_released_event& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.KeysDown[t_e.get_key_code()] = false;
    return false;
}

bool imgui_layer::on_key_typed(key_typed_event& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    int keycode = t_e.get_key_code();
    if (keycode > 0 && keycode < 0x10000) {
        io.AddInputCharacter((unsigned short)keycode);
    }
    return false;
}

bool imgui_layer::on_mouse_button_pressed(mouse_button_pressed_event& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.MouseDown[t_e.get_mouse_button()] = true;
    return false;
}

bool imgui_layer::on_mouse_button_released(mouse_button_released_event& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.MouseDown[t_e.get_mouse_button()] = false;
    return false;
}

bool imgui_layer::on_mouse_moved(mouse_moved_event& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos = ImVec2(t_e.get_pos().x, t_e.get_pos().y);
    return false;
}

bool imgui_layer::on_mouse_scrolled(mouse_scrolled_event& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.MouseWheel  += t_e.get_offset().y;
    io.MouseWheelH += t_e.get_offset().x;
    return false;
}

bool imgui_layer::on_window_resized(window_resized_event& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize = ImVec2(t_e.get_window_size().x, t_e.get_window_size().y);
    return false;
}

bool imgui_layer::on_window_framebuffer_resized(window_framebuffer_resized_event& t_e) {
    ImGuiIO &io = ImGui::GetIO();
    io.DisplayFramebufferScale = ImVec2(t_e.get_window_framebuffer_size().x / io.DisplaySize.x, t_e.get_window_framebuffer_size().y / io.DisplaySize.y);
    return false;
}

}
