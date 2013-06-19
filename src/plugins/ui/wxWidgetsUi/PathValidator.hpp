#ifndef PATH_BALIDATOR_HPP
#define PATH_BALIDATOR_HPP

#include <wx/validate.h>
#include "types.hpp"

namespace mru
{

class PathValidator : public wxValidator {
public:
  PathValidator(bool a_exists, bool a_is_directory, filepath_type *a_destination =NULL);
  ~PathValidator(void);
  PathValidator(const PathValidator &a_other);

  wxObject* Clone(void) const;
  bool Validate(wxWindow *a_parent);
  bool TransferToWindow(void);
  bool TransferFromWindow(void);

private:
  bool m_exists, m_is_directory;
  bool m_destination_specified;
  filepath_type *m_destination;
};

} /* namespace mru */

#endif /* PATH_BALIDATOR_HPP */

