#ifndef ERE_ECS_SCENE_HPP
#define ERE_ECS_SCENE_HPP

#include <entt/entt.hpp>
#include <ere/core/iLayer.hpp>
#include <ere/events/appEvents.hpp>

namespace ere {

class entity;
class scene : public iLayer {
public:
    
    friend class entity;

    entity createEntity();
    void destroyEntity(entity t_e);

    virtual void onEvent(ereEvent& t_event) final override;

private:

    entt::registry m_registry;

};

}


#endif
