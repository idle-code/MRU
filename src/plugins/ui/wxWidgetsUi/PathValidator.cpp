#include "PathValidator.hpp"
#include <wx/textctrl.h>
#include "glue.hpp"
#include <boost/filesystem.hpp>

namespace mru
{

namespace bfs = boost::filesystem;

PathValidator::PathValidator(bool a_exists, bool a_is_directory, filepath_type *a_destination)
  : m_exists(a_exists), m_is_directory(a_is_directory),
    m_destination_specified(a_destination != NULL), m_destination(a_destination)
{
  if(!m_destination_specified)
    a_destination = new filepath_type;
}

PathValidator::~PathValidator(void)
{
  if(!m_destination_specified)
    delete m_destination;
}

PathValidator::PathValidator(const PathValidator &a_other)
{
  m_exists = a_other.m_exists;
  m_is_directory = a_other.m_is_directory;
  m_destination_specified = a_other.m_destination_specified;
  if(m_destination_specified)
    m_destination = a_other.m_destination;
  else
    m_destination = new filepath_type;
}

wxObject *
PathValidator::Clone(void) const
{
  return new PathValidator(*this);
}

bool
PathValidator::Validate(wxWindow *a_parent)
{
  wxTextCtrl *control = dynamic_cast<wxTextCtrl*>(GetWindow());
  if(control == NULL)
    return false;

  wxString value = control->GetValue(); 
  if(m_exists && !bfs::exists(glue_cast<filepath_type>(value)))
    return false;
  if(m_is_directory && !bfs::is_directory(glue_cast<filepath_type>(value)))
    return false;

  return true;
}

bool
PathValidator::TransferToWindow(void)
{
  wxTextCtrl *control = dynamic_cast<wxTextCtrl*>(GetWindow());
  if(control == NULL)
    return false;
  control->SetValue(glue_cast<wxString>(*m_destination));
  return true; 
}

bool
PathValidator::TransferFromWindow(void)
{
  wxTextCtrl *control = dynamic_cast<wxTextCtrl*>(GetWindow());
  if(control == NULL)
    return false;
  *m_destination = glue_cast<filepath_type>(control->GetValue());
  return true; 
}

} /* namespace mru */

