#ifndef __ERE_FRAMEBUFFER_API_HPP__
#define __ERE_FRAMEBUFFER_API_HPP__

#include <ere/core/core.hpp>
#include "texture2d_api.hpp"
#include <glm/glm.hpp>

namespace ere {

class framebuffer_api {
public:

    inline static ref<framebuffer_api> create_framebuffer_api(glm::vec2 t_size) { return create_framebuffer_api(t_size.x, t_size.y); }
    static ref<framebuffer_api> create_framebuffer_api(int t_width, int t_height);
    static ref<framebuffer_api> get_default_framebuffer_api();
    static ref<framebuffer_api> get_current_framebuffer_api();

    virtual ~framebuffer_api() = default;

    virtual void bind() = 0;
    virtual void unbind() const = 0;

    virtual void disable_color_attachment() = 0;

    virtual int get_id() const = 0;

    virtual int get_width() const = 0;
    virtual int get_height() const = 0;

    virtual void resize(int t_width, int t_height) = 0;

    virtual bool is_valid() = 0;

    virtual void add_color_attachment(texture_api::format t_format = texture_api::format::RGB) = 0;
    virtual ref<texture2d_api> get_color_attachemt(int t_index = 0) const = 0;
    virtual const std::vector<ref<texture2d_api>>& get_color_attachments() const = 0;

    virtual void add_depth_attachment() = 0;
    virtual ref<texture2d_api> get_depth_attachemt() const = 0;

    virtual void add_stencil_attachment() = 0;
    virtual ref<texture2d_api> get_stencil_attachemt() const = 0;

    virtual void add_depth_stencil_attachment() = 0;
    virtual ref<texture2d_api> get_depth_stencil_attachemt() const = 0;

    virtual void add_depth_stencil_attachment_write_only() = 0;

    virtual void set_viewport(glm::vec2 t_size) = 0;
    virtual glm::vec2 get_viewport() const = 0;

protected:

    static ref<framebuffer_api> s_default_framebuffer;
    static weak_ref<framebuffer_api> s_current_framebuffer;

};

}

#endif
