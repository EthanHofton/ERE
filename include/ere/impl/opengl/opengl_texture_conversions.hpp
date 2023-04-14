#ifndef __ERE_OPENGL_TEXTURE_CONVERSIONS_HPP__
#define __ERE_OPENGL_TEXTURE_CONVERSIONS_HPP__

#include <ere/ere_config.hpp>
#ifdef USE_OPENGL
#include <glad/glad.h>

#include <ere/api/texture_api.hpp>

namespace ere {


inline GLenum get_gl_format(const texture_api::format& t_format) {
    switch (t_format) {
        case texture_api::format::RED:
            return GL_RED;
        case texture_api::format::RG:
            return GL_RG;
        case texture_api::format::RGB:
        case texture_api::format::RGB16F:
        case texture_api::format::RGB32F:
            return GL_RGB;
        case texture_api::format::RGBA:
        case texture_api::format::RGBA16F:
        case texture_api::format::RGBA32F:
            return GL_RGBA;
        case texture_api::format::DEPTH:
            return GL_DEPTH_COMPONENT;
        case texture_api::format::STENCIL:
            return GL_STENCIL_INDEX;
        case texture_api::format::DEPTH_STENCIL:
            return GL_DEPTH_STENCIL;
        default:
            return GL_RGBA;
    }
}
inline GLenum get_gl_internal_format(const texture_api::format& t_format) {
    switch (t_format) {
        case texture_api::format::RED:
            return GL_RED;
        case texture_api::format::RG:
            return GL_RG;
        case texture_api::format::RGB:
            return GL_RGB;
        case texture_api::format::RGB16F:
            return GL_RGB16F;
        case texture_api::format::RGB32F:
            return GL_RGB32F;
        case texture_api::format::RGBA:
            return GL_RGBA;
        case texture_api::format::RGBA16F:
            return GL_RGBA16F;
        case texture_api::format::RGBA32F:
            return GL_RGBA32F;
        case texture_api::format::DEPTH:
            return GL_DEPTH_COMPONENT;
        case texture_api::format::STENCIL:
            return GL_STENCIL_INDEX;
        case texture_api::format::DEPTH_STENCIL:
            return GL_DEPTH_STENCIL;
        default:
            return GL_RGBA;
    }
}
inline GLenum get_gl_filter(const texture_api::filter& t_filter) {
    switch (t_filter) {
        case texture_api::filter::LINEAR:
            return GL_LINEAR;
        case texture_api::filter::NEAREST:
            return GL_NEAREST;
        case texture_api::filter::LINEAR_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
        case texture_api::filter::LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        case texture_api::filter::NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        case texture_api::filter::NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        default:
            return GL_LINEAR;
    }
}
inline GLenum get_gl_wrap(const texture_api::wrap& t_wrap) {
    switch (t_wrap) {
        case texture_api::wrap::CLAMP_TO_EDGE:
            return GL_CLAMP_TO_EDGE;
        case texture_api::wrap::CLAMP_TO_BORDER:
            return GL_CLAMP_TO_BORDER;
        case texture_api::wrap::MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
        case texture_api::wrap::REPEAT:
            return GL_REPEAT;
        default:
            return GL_REPEAT;
    }
}
inline GLenum get_gl_type(const texture_api::format& t_format) {
    switch (t_format) {
        case texture_api::format::RED:
        case texture_api::format::RG:
        case texture_api::format::RGB:
        case texture_api::format::RGBA:
        case texture_api::format::DEPTH:
        case texture_api::format::STENCIL:
            return GL_UNSIGNED_BYTE;
        case texture_api::format::DEPTH_STENCIL:
            return GL_UNSIGNED_INT_24_8;
        case texture_api::format::RGB16F:
        case texture_api::format::RGB32F:
        case texture_api::format::RGBA16F:
        case texture_api::format::RGBA32F:
            return GL_FLOAT;
        default:
            return GL_UNSIGNED_BYTE;
    }
}

}

#endif

#endif // __ERE_OPENGL_TEXTURE_CONVERSIONS_HPP__
