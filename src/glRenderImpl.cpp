#include <ere/impl/opengl/glRenderImpl.hpp>
#include <ere/core/logger.hpp>

#ifdef USE_OPENGL
#include <glad/gl.h>

namespace ere {

    void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         ERE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       ERE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          ERE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: ERE_TRACE(message); return;
		}
	}

void glRenderImpl::init() {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(OpenGLMessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
}

void glRenderImpl::drawIndexed(const ref<vertexArrayAPI>& t_vertexArray, uint32_t t_indexCount) {
    t_vertexArray->bind();
    uint32_t count = t_indexCount ? t_indexCount : t_vertexArray->getIndexBuffer()->getCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}


}


#endif
