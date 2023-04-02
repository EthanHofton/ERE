#include <ere/api/renderAPI.hpp>

#include <ereConfig.hpp>
#ifdef USE_OPENGL

namespace ere {

class glRenderImpl : public renderAPI {

    virtual void init() override;
    virtual void setViewport(const glm::vec2& t_size) override;
    virtual void clearColor(const glm::vec4& t_color) override;
    virtual void clearBuffer() override;
    virtual void drawIndexed(const ref<vertexArrayAPI>& t_vertexArray, uint32_t t_indexCount = 0) override;

};

}

#endif
