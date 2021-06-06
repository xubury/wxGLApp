#include "GLPanel.hpp"
#include "Core/Assert.hpp"
#include <iostream>

GLPanel::GLPanel(wxWindow *parent, wxWindowID win_id, int *displayAttrs,
                 const wxPoint &pos, const wxSize &size, long style,
                 const wxString &name, const wxPalette &palette)
    : wxGLCanvas(parent, win_id, displayAttrs, pos, size, style, name, palette),
      m_context(new wxGLContext(this)),
      m_camera(te::createRef<Camera>(0, 0, 800, 600)) {
  this->SetCurrent(*m_context);
  m_renderer = te::createScope<Renderer>();
  Bind(wxEVT_PAINT, &GLPanel::onRendered, this);
  Bind(wxEVT_SIZE, &GLPanel::onResized, this);
}

void GLPanel::onRendered(wxPaintEvent &) {
  if (!IsShown())
    return;
  SetCurrent(*m_context);
  wxPaintDC(this);
  m_renderer->clear();
  m_renderer->render(m_camera);
  SwapBuffers();
}

void GLPanel::onResized(wxSizeEvent &event) {
  m_camera->setViewportSize(event.GetSize().GetWidth(),
                            event.GetSize().GetHeight());
  Refresh();
  event.Skip();
}
