#include "Renderer.hpp"
#include "Camera.hpp"
#include "Core/Log.hpp"
#include "Graphic/GLContext.hpp"
#include "Graphic/Primitive.hpp"

Renderer::Renderer() : m_camera(te::createRef<Camera>(0, 0, 800, 600))
{
    te::Log::init("Debug.log");
    te::GLContext::init(nullptr);

    // the main shader
    m_shader = te::createRef<te::Shader>();
    m_shader->load("vertex.glsl", "fragment.glsl");

    const char *shadowVertex = "#version 330 core\n"
                               "layout (location = 0) in vec3 aPos;\n"
                               "uniform mat4 uLightSpaceMatrix;\n"
                               "uniform mat4 uModel;\n"
                               "void main() {\n"
                               "    gl_Position = uLightSpaceMatrix * uModel * vec4(aPos, 1.0);\n"
                               "}";
    const char *shadowFragment = "#version 330 core\n"
                                 "void main() {\n"
                                 "}";

    // light caster shader
    m_lightShader = te::createRef<te::Shader>();
    m_lightShader->compile(shadowVertex, shadowFragment);
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
    m_camera->setPosition(glm::vec3(0, 0, 12));

    m_dirLight = te::createRef<Light>();
    m_dirLight->setPosition(glm::vec3(0, 0, 10));
    m_dirLight->setEulerAngle(glm::vec3(0, glm::radians(180.0), 0));
    m_dirLight->amibent = glm::vec3(0.5);
    m_dirLight->diffuse = glm::vec3(0.5);
    m_dirLight->specular = glm::vec3(0.5);
}

void Renderer::render()
{
    // drawing using custom shader
    // projection and view uniform should use name 'uProjection' and 'uView'
    te::RenderStates states;
    // normal drawing
    beginScene(m_shader, m_camera);
    clear();
    // m_buffer->draw(*this, states);
    // m_eBuffer->draw(*this, states);
    states.transform = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -2));
    m_model->draw(*this, states);
    endScene();

    // draw simple stuff in world space
    // te::Primitive::instance().setDrawingView(m_camera);
    // te::Primitive::instance().drawLine(glm::vec3(0), glm::vec3(1), glm::vec4(1.0), 10);
    // te::Primitive::instance().drawCircle(glm::vec3(0), glm::vec3(0, 1, 1), glm::vec4(1.0), 5);
}