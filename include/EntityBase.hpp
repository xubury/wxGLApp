#ifndef ENTITY_BASE_HPP
#define ENTITY_BASE_HPP

#include "ECS/ECS.hpp"
#include "Core/Transform.hpp"
#include "Graphic/Drawable.hpp"

class EntityBase : public te::Entity<EntityBase>, virtual public te::Transformable, public te::Drawable
{
  public:
    EntityBase(const EntityBase &) = delete;

    EntityBase &operator=(const EntityBase &) = delete;

    virtual ~EntityBase() = default;

    EntityBase(te::EntityManager<EntityBase> *manager, uint32_t id);

    std::string getName() const;

    void setName(const std::string &name);

    void draw(const te::Shader &shader, const glm::mat4 &transform) const;

  private:
    std::string m_name;
};

#endif