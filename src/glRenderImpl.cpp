#include <ere/impl/opengl/glRenderImpl.hpp>
#include <ere/core/logger.hpp>


#ifdef USE_OPENGL
#include <glad/gl.h>

#ifdef USE_GLFW
#include <GLFW/glfw3.h>
#endif

namespace ere {

// * GL > 4.3
// void OpenGLMessageCallback(
//     unsigned source,
//     unsigned type,
//     unsigned id,
//     unsigned severity,
//     int length,
//     const char* message,
//     const void* userParam)
// {
//     switch (severity)
//     {
//         case GL_DEBUG_SEVERITY_HIGH:         ERE_CRITICAL(message); return;
//         case GL_DEBUG_SEVERITY_MEDIUM:       ERE_ERROR(message); return;
//         case GL_DEBUG_SEVERITY_LOW:          ERE_WARN(message); return;
//         case GL_DEBUG_SEVERITY_NOTIFICATION: ERE_TRACE(message); return;
//     }
// }

void glRenderImpl::init() {
    // * initalize glad
    #ifdef USE_GLFW
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        ERE_CRITICAL("Failed to initalize GLAD");
        throw std::runtime_error("Failed to initalize GLAD");
    }
    #endif

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    // * required GL > 4.3
    // glDebugMessageCallback(OpenGLMessageCallback, nullptr);
    // glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
}
void glRenderImpl::setViewport(const glm::vec2& t_size) {
    glViewport(0, 0, t_size.x, t_size.y);
}
void glRenderImpl::clearColor(const glm::vec4& t_color) {
    glClearColor(t_color.r, t_color.g, t_color.b, t_color.a);
}
void glRenderImpl::clearBuffer() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void glRenderImpl::drawIndexed(const ref<vertexArrayAPI>& t_vertexArray, uint32_t t_indexCount) {
    t_vertexArray->bind();
    uint32_t count = t_indexCount ? t_indexCount : t_vertexArray->getIndexBuffer()->getCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

scope<renderAPI> renderAPI::make() {
    return createScope<glRenderImpl>();
}

}


#endif
