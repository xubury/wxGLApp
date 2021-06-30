#include "Cube.hpp"

#include "Graphic/Renderer.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/Vertex.hpp"

Cube::Cube(te::EntityManager<EntityBase> *manager, uint32_t id, float width, float height, float length,
           te::Ref<te::Material> material)
    : EntityBase(manager, id), m_material(material)
{
    width /= 2;
    height /= 2;
    length /= 2;
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0f,  1.0f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0f,  1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f, 1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f, 1.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f,  0.0f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f, 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  1.0f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,0.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,0.0f,  1.0f,  0.0f,  1.0f,  0.0f
    };
    m_cube = te::createRef<te::VertexArray>();
    te::Ref<te::VertexBuffer> vertexBuffer = te::createRef<te::VertexBuffer>(vertices, sizeof(vertices));
    vertexBuffer->setLayout({{te::ShaderDataType::Float3, "aPos"},
                             {te::ShaderDataType::Float2, "aTexCoord"},
                             {te::ShaderDataType::Float3, "aNormal"}});
    m_cube->addVertexBuffer(vertexBuffer);
}

void Cube::draw(const te::Shader &shader, const glm::mat4 &transform) const
{
    te::Renderer::submit(shader, *m_cube, te::GL_TRIANGLES, false, getTransform() * transform, m_material.get());
}