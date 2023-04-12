#ifndef __ERE_FRAMEBUFFER_API_HPP__
#define __ERE_FRAMEBUFFER_API_HPP__

#include <ere/core/core.hpp>
#include "texture_api.hpp"

namespace ere {

class framebuffer_api {
public:

    static ref<framebuffer_api> create_framebuffer_api();
    virtual ~framebuffer_api() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void disable_color_attachment() const = 0;

    virtual int get_id() const = 0;

    virtual int get_width() const = 0;
    virtual int get_height() const = 0;

    virtual bool is_valid() const = 0;

    virtual ref<texture_api> add_color_attachment() const = 0;
    virtual ref<texture_api> add_depth_attachment() const = 0;
    virtual ref<texture_api> add_stencil_attachment() const = 0;
    virtual ref<texture_api> add_depth_stencil_attachment() const = 0;
};

}

#endif
