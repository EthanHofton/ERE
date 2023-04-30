#ifndef __ERE_OPENGL_RENDERER_CONVERSIONS_HPP__
#define __ERE_OPENGL_RENDERER_CONVERSIONS_HPP__

#include <ere/ere_config.hpp>
#ifdef USE_OPENGL
#include <glad/glad.h>

#include <ere/api/render_api.hpp>

namespace ere {

extern inline GLenum get_gl_culling_face(render_api::culling_face t_face) {
    switch (t_face) {
        case render_api::culling_face::FRONT:
            return GL_FRONT;
        case render_api::culling_face::BACK:
            return GL_BACK;
        case render_api::culling_face::FRONT_AND_BACK:
            return GL_FRONT_AND_BACK;
    }
}

extern inline GLenum get_gl_culling_direction(render_api::culling_direction t_direction) {
    switch (t_direction) {
        case render_api::culling_direction::CLOCKWISE:
            return GL_CW;
        case render_api::culling_direction::COUNTER_CLOCKWISE:
            return GL_CCW;
    }
}

extern inline GLenum get_gl_testing_function(render_api::testing_function t_function) {
    switch (t_function) {
        case render_api::testing_function::NEVER:
            return GL_NEVER;
        case render_api::testing_function::LESS:
            return GL_LESS;
        case render_api::testing_function::EQUAL:
            return GL_EQUAL;
        case render_api::testing_function::LEQUAL:
            return GL_LEQUAL;
        case render_api::testing_function::GREATER:
            return GL_GREATER;
        case render_api::testing_function::NOTEQUAL:
            return GL_NOTEQUAL;
        case render_api::testing_function::GEQUAL:
            return GL_GEQUAL;
        case render_api::testing_function::ALWAYS:
            return GL_ALWAYS;
    }
}

extern inline GLenum get_gl_blending_function(render_api::blending_function t_function) {
    switch (t_function) {
        case render_api::blending_function::ZERO:
            return GL_ZERO;
        case render_api::blending_function::ONE:
            return GL_ONE;
        case render_api::blending_function::SRC_COLOR:
            return GL_SRC_COLOR;
        case render_api::blending_function::ONE_MINUS_SRC_COLOR:
            return GL_ONE_MINUS_SRC_COLOR;
        case render_api::blending_function::DST_COLOR:
            return GL_DST_COLOR;
        case render_api::blending_function::ONE_MINUS_DST_COLOR:
            return GL_ONE_MINUS_DST_COLOR;
        case render_api::blending_function::SRC_ALPHA:
            return GL_SRC_ALPHA;
        case render_api::blending_function::ONE_MINUS_SRC_ALPHA:
            return GL_ONE_MINUS_SRC_ALPHA;
        case render_api::blending_function::DST_ALPHA:
            return GL_DST_ALPHA;
        case render_api::blending_function::ONE_MINUS_DST_ALPHA:
            return GL_ONE_MINUS_DST_ALPHA;
        case render_api::blending_function::CONSTANT_COLOR:
            return GL_CONSTANT_COLOR;
        case render_api::blending_function::ONE_MINUS_CONSTANT_COLOR:
            return GL_ONE_MINUS_CONSTANT_COLOR;
        case render_api::blending_function::CONSTANT_ALPHA:
            return GL_CONSTANT_ALPHA;
        case render_api::blending_function::ONE_MINUS_CONSTANT_ALPHA:
            return GL_ONE_MINUS_CONSTANT_ALPHA;
    }
}

extern inline GLenum get_gl_stencil_operation(render_api::stencil_operation t_operation) {
    switch (t_operation) {
        case render_api::stencil_operation::KEEP:
            return GL_KEEP;
        case render_api::stencil_operation::ZERO:
            return GL_ZERO;
        case render_api::stencil_operation::REPLACE:
            return GL_REPLACE;
        case render_api::stencil_operation::INCR:
            return GL_INCR;
        case render_api::stencil_operation::INCR_WRAP:
            return GL_INCR_WRAP;
        case render_api::stencil_operation::DECR:
            return GL_DECR;
        case render_api::stencil_operation::DECR_WRAP:
            return GL_DECR_WRAP;
        case render_api::stencil_operation::INVERT:
            return GL_INVERT;
    }
}

extern inline GLenum get_gl_primitive(render_api::primitive t_primitive) {
    switch (t_primitive) {
        case render_api::primitive::POINTS:
            return GL_POINTS;
        case render_api::primitive::LINES:
            return GL_LINES;
        case render_api::primitive::LINE_LOOP:
            return GL_LINE_LOOP;
        case render_api::primitive::LINE_STRIP:
            return GL_LINE_STRIP;
        case render_api::primitive::TRIANGLES:
            return GL_TRIANGLES;
        case render_api::primitive::TRIANGLE_STRIP:
            return GL_TRIANGLE_STRIP;
        case render_api::primitive::TRIANGLE_FAN:
            return GL_TRIANGLE_FAN;
    }
}

}

#endif

#endif // __ERE_OPENGL_RENDERER_CONVERSIONS_HPP__
