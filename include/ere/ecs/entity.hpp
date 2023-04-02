#ifndef ERE_ECS_ENTITY_HPP
#define ERE_ECS_ENTITY_HPP

#include <ere/core/core.hpp>
#include "scene.hpp"

namespace ere {

class entity {
public:

    friend class scene;

    entity(entt::entity t_entity, weak_ref<scene> t_scene) : m_entity(t_entity), m_scene(t_scene) {}
    entity(const entity& other) = default;
    entity() = default;

    template<typename _componentType, typename... _args>
    std::enable_if_t<!std::is_pointer_v<_componentType>, _componentType&> addComponent(_args&&... t_args) {
        _componentType& comp = m_scene.lock()->m_registry.emplace<_componentType>(m_entity, _componentType(std::forward<_args>(t_args)...));
        return comp;
    }

    template<typename _componentType>
    std::enable_if_t<!std::is_pointer_v<_componentType>, _componentType&> getComponent() {
        return m_scene.lock()->m_registry.get<_componentType>(m_entity);
    }

    template<typename _componentType>
    std::enable_if_t<!std::is_pointer_v<_componentType>, bool> hasComponent() const {
        return m_scene.lock()->m_registry.all_of<_componentType>(m_entity);
    }

    template<typename _componentType>
    std::enable_if_t<!std::is_pointer_v<_componentType>, void> removeComponent() {
        m_scene.lock()->m_registry.remove<_componentType>(m_entity);
    }

    std::weak_ptr<scene> getScene() {
        return m_scene;
    }

    operator bool() const { return m_entity != entt::null; }
    operator entt::entity() const { return m_entity; }
    operator uint32_t() const { return (uint32_t)m_entity; }

    bool operator==(const entity& t_other) const {
        return m_entity == t_other.m_entity && m_scene.lock() == t_other.m_scene.lock();
    }
    bool operator!=(const entity& t_other) const {
        return !(*this == t_other);
    }

    bool null() const {
        return m_entity == entt::null;
    }

private:

    entt::entity m_entity;
    weak_ref<scene> m_scene;

};

}

#endif
