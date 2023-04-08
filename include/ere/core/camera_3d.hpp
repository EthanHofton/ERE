#ifndef __ERE_CAMERA_3D_HPP__
#define __ERE_CAMERA_3D_HPP__

#include <ere/api/camera_api.hpp>
#include <ere/events/app_events.hpp>
#include <ere/events/mouse_events.hpp>
#include <ere/events/key_events.hpp>
#include <ere/mappings/key_map.hpp>

namespace ere {

class camera_3d : public camera_api {
public:

    enum class camera_movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN,
    };

    camera_3d(float t_aspect_ratio);
    ~camera_3d() = default;

    virtual const glm::mat4& get_projection_matrix() override;
    virtual const glm::mat4& get_view_matrix() override;

    void on_update(update_event& t_event);
    void on_key_pressed(key_pressed_event& t_event);
    void on_mouse_moved(mouse_moved_event& t_event);
    void on_mouse_scrolled(mouse_scrolled_event& t_event);

    void set_position(const glm::vec3 t_position) { m_position = t_position; m_camera_updated = true; }
    void move(camera_movement t_direction);
    glm::vec3 get_position() const override { return m_position; }

    void set_world_up(const glm::vec3 t_up) { m_up = t_up; m_camera_updated = true; }
    const glm::vec3& get_world_up() const { return m_up; }

    void set_move_speed(float t_move_speed) { m_move_speed = t_move_speed; }
    float get_move_speed() const { return m_move_speed; }

    void set_turn_speed(float t_turn_speed) { m_turn_speed = t_turn_speed; }
    float get_turn_speed() const { return m_turn_speed; }

    void set_yaw(float t_yaw) { m_yaw = t_yaw; m_camera_updated = true; }
    float get_yaw() const { return m_yaw; }

    void set_pitch(float t_pitch) { m_pitch = t_pitch; m_camera_updated = true; }
    float get_pitch() const { return m_pitch; }

    void set_constrain_pitch(bool t_constrain_pitch) { m_constrain_pitch = t_constrain_pitch; }
    bool get_constrain_pitch() const { return m_constrain_pitch; }

    glm::vec3 get_camera_up() const { return m_up; }
    glm::vec3 get_camera_front() const { return m_front; }
    glm::vec3 get_camera_right() const { return m_right; }

    void set_aspect_ratio(float t_aspect_ratio) { m_aspect_ratio = t_aspect_ratio; m_projection_updated = true; }
    float get_aspect_ratio() const { return m_aspect_ratio; }

    void set_fov(float t_fov) { m_fov = t_fov; m_projection_updated = true; }
    float get_fov() const { return m_fov; }

    void set_near(float t_near) { m_near = t_near; m_projection_updated = true; }
    float get_near() const { return m_near; }

    void set_far(float t_far) { m_far = t_far; m_projection_updated = true; }
    float get_far() const { return m_far; }

    void enable_camera() { m_camera_active = true; }
    void disable_camera() { m_camera_active = false; }

private:

    void update_camera_vectors();
    void update_projection_matrix();

private:

    // matrices
    glm::mat4 m_projection_matrix = glm::mat4(1.0f);
    glm::mat4 m_view_matrix = glm::mat4(1.0f);

    // camera settings (configureable)
    glm::vec3 m_position = {0,0,0};
    glm::vec3 m_world_up = {0,1,0};
    float m_move_speed = 10.0f;
    float m_turn_speed = 15.0f;
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    bool m_constrain_pitch = true;

    // camera settings (calculated)
    glm::vec3 m_up;
    glm::vec3 m_front = {0,0,-1};
    glm::vec3 m_right;


    // projection settings
    float m_aspect_ratio;
    float m_fov = 45.0f;
    float m_near = 0.1f;
    float m_far = 100.0f;

    // dirty flags
    bool m_camera_updated = true;
    bool m_projection_updated = true;

    bool m_first_mouse = true;

    bool m_camera_active = true;

};

}

#endif // __ERE_CAMERA_3D_HPP__
