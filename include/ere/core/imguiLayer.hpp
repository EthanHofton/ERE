#ifndef ERE_CORE_IMGUI_LAYER_HPP
#define ERE_CORE_IMGUI_LAYER_HPP

#include <ere/core/layer.hpp>

namespace ere {

class imguiLayer : public layer {
public:

    void begin(const double& t_delta, const glm::vec2& t_winSize, const glm::vec2& t_framebuffSize);
    void end();

    virtual bool onAttach(attachEvent& t_e) final override;
    virtual bool onDetach(detachEvent& t_e) final override;

    virtual bool onKeyPressed(keyPressedEvent& t_e) final override;
    virtual bool onKeyReleased(keyReleasedEvent& t_e) final override;
    virtual bool onKeyTyped(keyTypedEvent& t_e) final override;
    virtual bool onMouseButtonPressed(mouseButtonPressedEvent& t_e) final override;
    virtual bool onMouseButtonReleased(mouseButtonReleasedEvent& t_e) final override;
    virtual bool onMouseMoved(mouseMovedEvent& t_e) final override;
    virtual bool onMouseScrolled(mouseScrolledEvent& t_e) final override;
    virtual bool onWindowResize(windowResizeEvent& t_e) final override;
    virtual bool onWindowFramebufferResize(windowFramebufferResizeEvent& t_e) final override;
};

}

#endif
