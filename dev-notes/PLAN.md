# ERE Development Plan

## Abstractions

Abstract away platform specific implamentations. Window will abstract platform specific window mamangement, Renderer will abstract away renderer specific details. Only the abstract base class should be used.

@startuml

object window

object osx_window
object windows_window
object linux_window

object renderer

object opengl_window
object metal_window
object vulkan_window

window --> osx_window
window --> windows_window
window --> linux_window

renderer --> opengl_window
renderer --> metal_window
renderer --> vulkan_window

@enduml


## Public APIs

The following class diagrams will represent the (current) public APIs

### Window

@startuml
abstract class window {
    + {static} ref<window> create_concreate()
    + {abstract} void create_window(const windowProps&)
    + {abstract} void destroy_window()
    + {abstract} void set_window_size(glm::vec2&)
    + {abstract} void set_window_pos(glm::vec2&)
    + {abstract} void set_window_title(const std::string&)
    + {abstract} void set_window_swap_interval(const int&)
    + {abstract} void set_window_background_color(const glm::vec4&)
    + {abstract} glm::vec2 get_window_size()
    + {abstract} glm::vec2 get_window_pos()
    + {abstract} glm::vec2 get_window_framebuffer_size()
    + {abstract} void maximize_window()
    + {abstract} void minimize_window()
    + {abstract} void restore_window()
    + {abstract} void pre_render()
    + {abstract} void post_render()
}
@enduml

### Renderer

@startuml
abstract class renderer {
    + {static} ref<renderer> get_renderer()
    + {static} void set_viewport(const glm::vec2&)
    + {static} void clear_color(const glm::vec4&)
    + {static} void clear_buffer():
    + {static} void draw_data(render_data, render_buffer);
    + {static} void draw_line(const glm::vec2&, const glm::vec2&, const glm::vec4)
    + {static} void draw_point(const glm::vec2&, const glm::vec4)
    + {static} void draw_rect(const glm::vec2&, const glm::vec2, const glm::vec2, const glm::vec2, const glm::vec4)
}
@enduml


## Control Flow

The backend control flow can be seen as follows. The backend sends an update event (and imgui update event), this is then handeled by the users, where they will use the renderer to draw to the screen, the screens buffer is then swapped in the post renderer method and displayed on the next frame

@startuml

start

:Create application from user defined function (application::create());
:application::run();
while (running?) is (yes)
    :window::pre_render();
    :send update event (to be handled by user);
    :send ImGui Update event (to be handled by user);
    :ImGui render;
    :window::post_render();
endwhile (no)
stop
@enduml

All the frontend process entails is the user defining the create application method, which returns an application with layers attached to it. Each layer has event listener functions which get triggered by the back end whenever the events happen. On the update event, the user should use the renderAPI to draw to the screen each frame


@startuml

Application --> Layer: triggers event
Layer --> Renderer: calls render methods
Renderer --> Application: swapps window buffers

@enduml


# Release Plan

## Release v1.0.0 (project setup)

  1. Project and CMake setup
  2. Entry Point
  3. Application Class
  4. Event system
  5. Window Class
  6. Layer Class
  7. ImGui Layer
  8. Renderer and support classes

## Release v1.1.0 (ECS)

  1. E(ntity) C(omponrnt) S(ystem) setup
  2. Tag and UUID component
  3. Transform Component
  4. Mesh component
  5. Material Component

## Release v1.2.0 (Physics) (TBD)

  1. Physics Body Component
  2. Collider Component


## Release v1.3.0 (Post Processing) (TBD)
## Release v1.4.0 (Scripting) (TBD)

