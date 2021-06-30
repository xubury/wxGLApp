#include "EntityBase.hpp"

ES_INIT_ENTITY(EntityBase)

EntityBase::EntityBase(te::EntityManager<EntityBase> *manager, uint32_t id)
    : te::Entity<EntityBase>(manager, id) {
    m_name = "???";
}

void EntityBase::setName(const std::string &name) { m_name = name; }

std::string EntityBase::getName() const { return m_name; }

void EntityBase::draw(const te::Shader &, const glm::mat4 &) const {}
