#ifndef GL_PANEL_HPP
#define GL_PANEL_HPP

#include "Core/Base.hpp"
#include "Graphic/CameraBase.hpp"
#include "Graphic/GLContext.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Renderer.hpp"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/glcanvas.h>

class Camera : public te::CameraBase {
public:
  Camera(int x, int y, int width, int height)
      : te::CameraBase(x, y, width, height), m_transform(1.0f) {}

  virtual glm::mat4 getView() const override {
    return glm::lookAt(glm::vec3(0, 0, 10.f), glm::vec3(0.f),
                       glm::vec3(0, 1.f, 0));
  }

  virtual glm::mat4 getProjection() const override {
    return glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.0f);
  };

private:
  glm::mat4 m_transform;
};

class GLPanel : public wxGLCanvas {
public:
  GLPanel(wxWindow *parent, wxWindowID win_id, int *displayAttrs = nullptr,
          const wxPoint &pos = wxDefaultPosition,
          const wxSize &size = wxDefaultSize, long style = 0,
          const wxString &name = wxGLCanvasName,
          const wxPalette &palette = wxNullPalette);

  void onRendered(wxPaintEvent &event);

  void onResized(wxSizeEvent &event);

private:
  wxGLContext *m_context;
  te::Ref<Camera> m_camera;
  te::Scope<Renderer> m_renderer;
};

#endif /* GL_PANEL_HPP */
