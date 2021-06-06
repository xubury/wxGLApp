#include "Renderer.hpp"
#include "Core/Log.hpp"
#include "Graphic/GLContext.hpp"

Renderer::Renderer() {
  te::Log::init("Debug.log");
  te::GLContext::init(nullptr);
  const char *vetexCode = "#version 330 core\n"
                          "layout (location = 0) in vec3 aPos;\n"
                          "void main() {\n"
                          "    gl_Position =  vec4(aPos, 1.0f);\n"
                          "}";

  const char *fragmentCode = "#version 330 core\n"
                             "out vec4 fragColor;\n"
                             "uniform vec4 color;"
                             "void main() {\n"
                             "    fragColor = color;\n"
                             "}";

  m_shader = te::createRef<te::Shader>();
  m_shader->compile(vetexCode, fragmentCode);
  m_shader->bind();
  m_shader->setVec4("color", glm::vec4(0, 0, 1.0, 1.0));

  te::Vertex vertices[3];
  vertices[0].position = glm::vec3(-0.5, -0.5, 0);
  vertices[1].position = glm::vec3(0, -0.5, 0);
  vertices[2].position = glm::vec3(0, 0.5, 0);

  m_buffer = te::createRef<te::VertexBuffer>();
  m_buffer->update(vertices, 3, te::GL_TRIANGLES, te::GL_DYNAMIC_DRAW);
}

void Renderer::render(const te::Ref<te::CameraBase> &camera) {
  te::RenderStates states;
  beginScene(m_shader, camera);
  m_buffer->draw(*this, states);
  endScene();
}