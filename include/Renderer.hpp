#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <Graphic/RenderTarget.hpp>
#include <Graphic/Shader.hpp>
#include <Graphic/VertexBuffer.hpp>

class Renderer : public te::RenderTarget {
public:
  Renderer();
  void render(const te::Ref<te::CameraBase> &camera);

private:
  te::Ref<te::Shader> m_shader;
  te::Ref<te::VertexBuffer> m_buffer;
};

#endif // RENDERER_HPP