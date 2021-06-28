#include "GLPanel.hpp"
#include "Core/Math.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

GLPanel::GLPanel(wxWindow *parent, wxWindowID win_id, int *displayAttrs, const wxPoint &pos, const wxSize &size,
                 long style, const wxString &name, const wxPalette &palette)
    : wxGLCanvas(parent, win_id, displayAttrs, pos, size, style, name, palette), m_context(new wxGLContext(this)),
      m_camera(0, 0, size.GetWidth(), size.GetHeight()), m_isFirstMouse(true)
{
    this->SetCurrent(*m_context);

    te::GLContext::init(nullptr);
    te::Renderer::init();
    te::Log::init("Debug.log");

    m_shader = te::createRef<te::Shader>();

    m_shader->loadFromFile("vertex.glsl", "fragment.glsl");

    // 创建一个绘制对象(VAO)
    m_quad = te::createRef<te::VertexArray>();
    float quadVertices[] = {
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,
    };

    // 这个相当于VBO
    te::Ref<te::VertexBuffer> buffer = te::createRef<te::VertexBuffer>(quadVertices, sizeof(quadVertices));
    // 指定VBO在shader里的layout
    buffer->setLayout({{te::ShaderDataType::Float3, "aPos"}, {te::ShaderDataType::Float2, "aTexCoord"}});
    m_quad->addVertexBuffer(buffer);
    // m_quad->setIndexBuffer(...); 也可以设置索引绘制，不过submit的时候bool indexed要设置为true

    m_camera.translateWorld(glm::vec3(2, 2, 2));
    m_camera.rotateLocal(glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f));
    m_camera.rotateLocal(glm::radians(-45.f), glm::vec3(1.f, 0.f, 0.f));

    // 创建一个材质，用于后面submit绘制
    m_material = te::createRef<te::Material>();
    te::RandomGenerator random;

    float r = random.rnd(0.5, 1.0);
    float g = random.rnd(0.5, 1.0);
    float b = random.rnd(0.5, 1.0);
    m_material->loadFromValue(0.5f * glm::vec3(r, g, b), te::Material::TEXTURE_AMBIENT);
    m_material->loadFromValue(glm::vec3(r, g, b), te::Material::TEXTURE_DIFFUSE);
    m_material->loadFromValue(glm::vec3(0.5f), te::Material::TEXTURE_SPECULAR);

    Bind(wxEVT_PAINT, &GLPanel::onRendered, this);
    Bind(wxEVT_SIZE, &GLPanel::onResized, this);
    Bind(wxEVT_MOTION, &GLPanel::onMouseMove, this);
}

void GLPanel::onRendered(wxPaintEvent &)
{
    if (!IsShown())
        return;
    SetCurrent(*m_context);
    wxPaintDC(this);
    // 绘制首先指定绘制的相机和framebuffer， frambuffer不指定则设置为默认
    te::Renderer::beginScene(m_camera);
    te::Renderer::clear();

    // VAO对象的世界坐标变换
    glm::mat4 transform(1.0);
    transform = glm::translate(transform, glm::vec3(0, 0, -2));
    // 绘制一个VAO对象
    te::Renderer::submit(*m_shader, *m_quad, (te::GLenum)GL_TRIANGLE_STRIP, false, transform, m_material.get());

    // 在世界坐标系下，绘制接口默认提供的一些图形, 不接收shader, 使用当前相机的projection * view
    te::Primitive::instance().drawSphere(glm::vec3(0), glm::vec4(0, 1, 0, 1), 0.5f, 20, 20);
    te::Primitive::instance().drawSphereFilled(glm::vec3(0), glm::vec4(1), 0.1f, 20, 20);
    // X axis
    te::Primitive::instance().drawLine(glm::vec3(0), glm::vec3(1, 0, 0), glm::vec4(1, 0, 0, 1), 5);
    // Y axis
    te::Primitive::instance().drawLine(glm::vec3(0), glm::vec3(0, 1, 0), glm::vec4(0, 1, 0, 1), 5);
    // Z axis
    te::Primitive::instance().drawLine(glm::vec3(0), glm::vec3(0, 0, 1), glm::vec4(0, 0, 1, 1), 5);

    // 结束绘制
    te::Renderer::endScene();

    SwapBuffers();
}

void GLPanel::onResized(wxSizeEvent &event)
{
    Refresh();
    m_camera.setViewportSize(event.GetSize().GetWidth(), event.GetSize().GetHeight());
    event.Skip();
}

void GLPanel::onMouseMove(wxMouseEvent &event)
{
    wxPoint mousePos = event.GetPosition();
    if (event.ButtonIsDown(wxMOUSE_BTN_LEFT))
    {
        if (!m_isFirstMouse)
        {
            wxPoint offset = (mousePos - m_mouseClickPos);
            glm::mat4 transform(1.0f);
            const glm::vec3 &cameraleft = m_camera.getLeft();
            const glm::vec3 &rotateAround = glm::vec3(0, 0, 0);
            transform = glm::translate(transform, rotateAround);
            transform = glm::rotate(transform, glm::radians((float)-offset.x), glm::vec3(0.f, 1.f, 0.f));
            transform = glm::rotate(transform, glm::radians((float)-offset.y), cameraleft);
            transform = glm::translate(transform, -rotateAround);
            m_camera.setTransform(transform * m_camera.getTransform());
        }
        else
        {
            m_isFirstMouse = false;
        }
    }
    m_mouseClickPos = mousePos;
    Refresh();
    event.Skip();
}