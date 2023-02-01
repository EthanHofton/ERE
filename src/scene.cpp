#include <ere/ecs/scene.hpp>
#include <ere/ecs/entity.hpp>

namespace ere {

entity scene::createEntity() {
    entity e(m_registry.create(), this);
    e.addComponent<ere::uuid>();
    return e;
}

void scene::destroyEntity(entity t_e) {
    m_registry.destroy(t_e.m_entity);
}

void scene::onEvent(ereEvent &t_event) {
    util::event_dispatcher<ereEvents> dispatcher(t_event);
    dispatcher.dispatch<updateEvent>(std::bind(&scene::onUpdate, this, std::placeholders::_1));
}

bool scene::onUpdate(updateEvent& t_e) {
    return false;
}

}
