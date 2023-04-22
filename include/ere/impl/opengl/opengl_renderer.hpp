#ifndef __ERE_OPENGL_RENDERER_HPP__
#define __ERE_OPENGL_RENDERER_HPP__

#include <ere/ere_config.hpp>
#include <ere/api/render_api.hpp>

#ifdef USE_OPENGL
#include <glad/glad.h>
#include "opengl_renderer_conversions.hpp"

namespace ere {

class opengl_renderer : public render_api {
public:

    virtual void init_impl() override;

    virtual void set_viewport_impl(const glm::vec2& t_size) override;
    virtual glm::vec2 get_viewport_impl() const override;

    virtual void clear_color_impl(const glm::vec4& t_color) override;

    virtual void clear_buffers_impl() override;
    virtual void clear_color_buffer_impl() override;
    virtual void clear_depth_buffer_impl() override;
    virtual void clear_stencil_buffer_impl() override;

    virtual void enable_wireframe_impl() override;
    virtual void disable_wireframe_impl() override;

    virtual void enable_depth_testing_impl() override;
    virtual void enable_depth_test_write_impl() override;
    virtual void disable_depth_testing_impl() override;
    virtual void disable_depth_test_write_impl() override;
    virtual void set_depth_testing_function_impl(const render_api::testing_function& t_function) override;

    virtual void enable_blending_impl() override;
    virtual void disable_blending_impl() override;
    virtual void set_blending_function_impl(const render_api::blending_function& t_source, const render_api::blending_function& t_destination) override;

    virtual void enable_stencil_testing_impl() override;
    virtual void disable_stencil_testing_impl() override;
    virtual void set_stencil_mask_impl(unsigned char t_mask) override;
    virtual void set_stencil_function_impl(const render_api::testing_function& t_function, int t_reference, unsigned char t_mask) override;
    virtual void set_stencil_operation_impl(const render_api::stencil_operation& t_fail, const render_api::stencil_operation& t_pass_depth_fail, const render_api::stencil_operation& t_pass_depth_pass) override;

    virtual void enable_culling_impl(const render_api::culling_face& t_face, const render_api::culling_direction& t_direction) override;
    virtual void disable_culling_impl() override;

    virtual void pre_window_setup_impl() override;

    virtual void draw_indexed_impl(const ref<vertex_array_api>& t_vao) override;
    virtual void draw_arrays_impl(const ref<vertex_array_api>& t_vao, int t_vertex_count) override;
    virtual void draw_indexed_instanced_impl(const ref<vertex_array_api>& t_vao, int t_instance_count) override;
    virtual void draw_arrays_instanced_impl(const ref<vertex_array_api>& t_vao, int t_vertex_count, int t_instance_count) override;

};

}

#endif

#endif // __ERE_OPENGL_RENDERER_HPP__
