#include "TreeFrame.hpp"

#undef NDEBUG_L
#include <debug_l.h>

namespace mru
{

TreeFrame::TreeFrame(wxWindow *a_parent)
  : wxFrame(a_parent, -1, wxT("Tags"))
{ }

TreeFrame::~TreeFrame(void)
{ }

bool
TreeFrame::OnInit(void)
{
  FO("TreeFrame::OnInit(void)");



  return true;
} 

} /* namespace mru */

