#ifndef TREEFRAME_HPP
#define TREEFRAME_HPP

#include <wx/wx.h>

namespace mru
{

class TreeFrame : public wxFrame {
public:
  typedef TreeFrame self_type;
public:
  TreeFrame(wxWindow *a_parent=NULL);
  ~TreeFrame(void);

  bool OnInit(void);
};

} /* namespace mru */

#endif /* TREEFRAME_HPP */

