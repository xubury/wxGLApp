#include <GLPanel.hpp>
#include <MainApp.hpp>

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
    wxInitAllImageHandlers();
    auto *frame = new wxFrame(nullptr, wxID_ANY, "GL frame", wxPoint(50, 50), wxSize(800, 600));
    auto *sizer = new wxBoxSizer(wxHORIZONTAL);
    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, WX_GL_STENCIL_SIZE, 8, 0};
    auto *glPanel = new GLPanel(frame, wxID_ANY, args);
    sizer->Add(glPanel, 1, wxEXPAND);
    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    frame->Show();
    return true;
}
