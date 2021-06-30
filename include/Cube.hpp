
#include "EntityBase.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/Material.hpp"

class Cube : public EntityBase {
   public:
    Cube(te::EntityManager<EntityBase> *manager, uint32_t id, float width,
         float height, float length, te::Ref<te::Material> material);

    void draw(const te::Shader &shader, const glm::mat4 &transform) const override;

   private:
    te::Ref<te::VertexArray> m_cube;

    te::Ref<te::Material> m_material;
};
