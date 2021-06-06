#ifndef MAIN_APP_HPP
#define MAIN_APP_HPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MainApp : public wxApp {
public:
  virtual bool OnInit() override;
};

DECLARE_APP(MainApp)

#endif
