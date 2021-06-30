#ifndef GL_PANEL_HPP
#define GL_PANEL_HPP

#include "Graphic/Shader.hpp"
#include "Graphic/Camera.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/Buffer.hpp"
#include "Graphic/GLContext.hpp"
#include "Graphic/Renderer.hpp"
#include "Graphic/Primitive.hpp"

#include "Cube.hpp"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/glcanvas.h>

class GLPanel : public wxGLCanvas
{
  public:
    GLPanel(wxWindow *parent, wxWindowID win_id, int *displayAttrs = nullptr, const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize, long style = 0, const wxString &name = wxGLCanvasName,
            const wxPalette &palette = wxNullPalette);

    void onRendered(wxPaintEvent &event);

    void onResized(wxSizeEvent &event);

    void onMouseMove(wxMouseEvent &event);
  private:
    wxGLContext *m_context;
    te::Ref<te::Shader> m_shader;
    te::Camera m_camera;
    te::Ref<te::VertexArray> m_quad;
    te::Ref<te::Material> m_material;

    bool m_isFirstMouse;
    wxPoint m_mouseClickPos;

    te::SceneManager<EntityBase> m_scene;
};

#endif /* GL_PANEL_HPP */
