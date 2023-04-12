#ifndef __ERE_FRAMEBUFFER_API_HPP__
#define __ERE_FRAMEBUFFER_API_HPP__

#include <ere/core/core.hpp>
#include "texture_api.hpp"
#include <glm/glm.hpp>

namespace ere {

class framebuffer_api {
public:

    inline static ref<framebuffer_api> create_framebuffer_api(glm::vec2 t_size) { return create_framebuffer_api(t_size.x, t_size.y); }
    static ref<framebuffer_api> create_framebuffer_api(int t_width, int t_height);
    virtual ~framebuffer_api() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void disable_color_attachment() const = 0;

    virtual int get_id() const = 0;

    virtual int get_width() const = 0;
    virtual int get_height() const = 0;

    virtual bool is_valid() const = 0;

    virtual ref<texture_api> add_color_attachment() = 0;
    virtual ref<texture_api> get_color_attachemt() const = 0;
    virtual ref<texture_api> add_depth_attachment() = 0;
    virtual ref<texture_api> get_depth_attachemt() const = 0;
    virtual ref<texture_api> add_stencil_attachment() = 0;
    virtual ref<texture_api> get_stencil_attachemt() const = 0;
    virtual ref<texture_api> add_depth_stencil_attachment() = 0;
    virtual ref<texture_api> get_depth_stencil_attachemt() const = 0;
    virtual void add_depth_stencil_attachment_write_only() = 0;
};

}

#endif
