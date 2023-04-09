#include <ere/core/camera_3d.hpp>
#include <ere/core/application.hpp>

namespace ere {

camera_3d::camera_3d() { 
    m_aspect_ratio = application::get_application()->get_window_size().x / application::get_application()->get_window_size().y;
    update_camera_vectors(); 
    update_projection_matrix(); 
}

void camera_3d::update_camera_vectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));

    m_view_matrix = glm::lookAt(m_position, m_position + m_front, m_up);
    m_camera_updated = false;
}

void camera_3d::update_projection_matrix() {
    m_projection_matrix = glm::perspective(glm::radians(m_fov), m_aspect_ratio, m_near, m_far);
    m_projection_updated = false;
}

const glm::mat4& camera_3d::get_projection_matrix() {
    if (m_projection_updated) {
        update_projection_matrix();
    }
    return m_projection_matrix;
}

const glm::mat4& camera_3d::get_view_matrix() {
    if (m_camera_updated) {
        update_camera_vectors();
    }
    return m_view_matrix;
}

void camera_3d::on_key_pressed(key_pressed_event& t_event) {
    if (t_event.get_key_code() == ERE_KEY_ESCAPE) {
        if (m_camera_active) {
            m_camera_active = false;
            application::get_application()->set_relative_mouse_mode(false);
        } else {
            m_camera_active = true;
            application::get_application()->set_relative_mouse_mode(true);
        }
    }
}

void camera_3d::on_update(update_event& t_event) {
    if (!m_camera_active) {
        return;
    }

    if (application::get_application()->is_key_pressed(ERE_KEY_W)) {
        move(camera_movement::FORWARD);
    }

    if (application::get_application()->is_key_pressed(ERE_KEY_S)) {
        move(camera_movement::BACKWARD);
    }

    if (application::get_application()->is_key_pressed(ERE_KEY_A)) {
        move(camera_movement::LEFT);
    }

    if (application::get_application()->is_key_pressed(ERE_KEY_D)) {
        move(camera_movement::RIGHT);
    }

    if (application::get_application()->is_key_pressed(ERE_KEY_SPACE)) {
        move(camera_movement::UP);
    }

    if (application::get_application()->is_key_pressed(ERE_KEY_LEFT_SHIFT)) {
        move(camera_movement::DOWN);
    }
}

void camera_3d::on_mouse_moved(mouse_moved_event& t_event) {
    if (!m_camera_active) {
        return;
    }

    if (m_first_mouse) {
        m_first_mouse = false;
        return;
    }
    float x_offset = t_event.get_delta_pos().x;
    float y_offset = t_event.get_delta_pos().y;

    x_offset *= m_turn_speed * application::get_application()->get_delta_time();
    y_offset *= m_turn_speed * application::get_application()->get_delta_time();

    m_yaw += x_offset;
    m_pitch += y_offset;

    if (m_constrain_pitch) {
        if (m_pitch > 89.0f) {
            m_pitch = 89.0f;
        }
        if (m_pitch < -89.0f) {
            m_pitch = -89.0f;
        }
    }

    m_camera_updated = true;
}

void camera_3d::on_mouse_scrolled(mouse_scrolled_event& t_event) {
    if (!m_camera_active) {
        return;
    }

    m_fov -= t_event.get_offset().y;

    if (m_fov < 1.0f) {
        m_fov = 1.0f;
    }
    if (m_fov > 45.0f) {
        m_fov = 45.0f;
    }

    m_projection_updated = true;
}

void camera_3d::on_window_resized(window_resized_event& t_event) {
    m_aspect_ratio = static_cast<float>(t_event.get_window_size().x) / static_cast<float>(t_event.get_window_size().y);
    m_projection_updated = true;
}

void camera_3d::move(camera_movement t_direction) {
    float velocity = m_move_speed * application::get_application()->get_delta_time();
    switch (t_direction) {
        case camera_movement::FORWARD:
            m_position += m_front * velocity;
            break;
        case camera_movement::BACKWARD:
            m_position -= m_front * velocity;
            break;
        case camera_movement::LEFT:
            m_position -= m_right * velocity;
            break;
        case camera_movement::RIGHT:
            m_position += m_right * velocity;
            break;
        case camera_movement::UP:
            m_position += m_up * velocity;
            break;
        case camera_movement::DOWN:
            m_position -= m_up * velocity;
            break;
        default:
            break;
    }
    m_camera_updated = true;
}

} // namespace ere
