#include "Renderer.hpp"
#include "Camera.hpp"
#include "Core/Log.hpp"
#include "Graphic/GLContext.hpp"
#include "Graphic/Primitive.hpp"

Renderer::Renderer() : m_camera(te::createRef<Camera>(0, 0, 800, 600))
{
    te::Log::init("Debug.log");
    te::GLContext::init(nullptr);

    m_shader = te::createRef<te::Shader>();
    m_shader->load("vertex.glsl", "fragment.glsl");
    m_shader->bind();
    m_shader->setVec4("color", glm::vec4(0, 0, 1.0, 1.0));

    // how to set up a vertex buffer
    te::Vertex triangle[3];
    triangle[0].position = glm::vec3(-1, -1, 0);
    triangle[1].position = glm::vec3(0, -1, 0);
    triangle[2].position = glm::vec3(0, 1, 0);
    m_buffer = te::createRef<te::VertexBuffer>();
    m_buffer->update(triangle, 3, te::GL_TRIANGLES, te::GL_STATIC_DRAW);

    // how to set up a vertex buffer with index
    te::Vertex quad[4];
    quad[0].position = glm::vec3(0.5f, 0.5f, 0.0f);
    quad[1].position = glm::vec3(0.5f, -0.5f, 0.0f);
    quad[2].position = glm::vec3(-0.5f, -0.5f, 0.0f);
    quad[3].position = glm::vec3(-0.5f, 0.5f, 0.0f);
    unsigned int indices[] = {0, 1, 3, 1, 2, 3};
    m_eBuffer = te::createRef<te::ElementBuffer>();
    m_eBuffer->update(quad, 4, indices, 6, te::GL_TRIANGLES, te::GL_STATIC_DRAW);

    // load a model
    m_model = te::createRef<te::Model>();
    m_model->loadModel("backpack/backpack.obj");

    // move the camera
    m_camera->translateLocal(glm::vec3(0, 0, 12));
}

void Renderer::render()
{
    // drawing using custom shader
    // projection and view uniform should use name 'uProjection' and 'uView'
    te::RenderStates states;
    beginScene(m_shader, m_camera);
    m_buffer->draw(*this, states);
    m_eBuffer->draw(*this, states);
    m_model->draw(*this, states);
    endScene();

    // draw simple stuff in world space without a shader
    te::Primitive::instance().setDrawingView(m_camera);
    te::Primitive::instance().drawLine(glm::vec3(0), glm::vec3(1), glm::vec4(1.0), 10);
    te::Primitive::instance().drawCircle(glm::vec3(0), glm::vec3(0, 1, 1), glm::vec4(1.0), 5);
}