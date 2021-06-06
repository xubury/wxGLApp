#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Graphic/RenderTarget.hpp"
#include "Graphic/Shader.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/ElementBuffer.hpp"
#include "Graphic/Model.hpp"
#include "Camera.hpp"

class Renderer : public te::RenderTarget
{
  public:
    Renderer();
    void render();

    te::Ref<Camera> &getCamera()
    {
        return m_camera;
    }

  private:
    te::Ref<te::Shader> m_shader;
    te::Ref<te::VertexBuffer> m_buffer;
    te::Ref<te::ElementBuffer> m_eBuffer;
    te::Ref<te::Model> m_model;
    te::Ref<Camera> m_camera;
};

#endif // RENDERER_HPP