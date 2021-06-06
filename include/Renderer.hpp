#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <Graphic/RenderTarget.hpp>
#include <Graphic/Shader.hpp>
#include <Graphic/VertexBuffer.hpp>

class Renderer : public te::RenderTarget
{
  public:
    Renderer();
    void render();

    te::Ref<te::CameraBase> &getCamera()
    {
        return m_camera;
    }

  private:
    te::Ref<te::Shader> m_shader;
    te::Ref<te::VertexBuffer> m_buffer;
    te::Ref<te::CameraBase> m_camera;
};

#endif // RENDERER_HPP