#ifndef ERE_ECS_SCENE_HPP
#define ERE_ECS_SCENE_HPP

#include <entt/entt.hpp>
#include <ere/core/layer.hpp>
#include <ere/events/appEvents.hpp>
#include <ere/components/uuid.hpp>

namespace ere {

class entity;
class scene : public layer, public std::enable_shared_from_this<scene> {
public:
    
    friend class entity;

    entity createEntity();
    void destroyEntity(entity t_e);

private:

    entt::registry m_registry;

};

}


#endif
