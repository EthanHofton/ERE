#include <ere/ecs/scene.hpp>
#include <ere/ecs/entity.hpp>

namespace ere {

entity scene::createEntity() {
    entity e(m_registry.create(), shared_from_this());
    e.addComponent<ere::uuid>();
    return e;
}

void scene::destroyEntity(entity t_e) {
    m_registry.destroy(t_e.m_entity);
}


}
