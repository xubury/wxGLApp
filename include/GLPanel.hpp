#ifndef GL_PANEL_HPP
#define GL_PANEL_HPP

#include "Renderer.hpp"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/glcanvas.h>

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
  te::Scope<Renderer> m_renderer;
};

#endif /* GL_PANEL_HPP */
