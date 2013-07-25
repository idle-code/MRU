#ifndef TEXT_CASE_TAG_HPP
#define TEXT_CASE_TAG_HPP

#include <plugins/MetatagPlugin.hpp>

namespace mru
{

class TextCaseMetatag : public MetatagPlugin {
public:
  PLUGIN_NAME("TextCase")
  TextCaseMetatag(void);
  ~TextCaseMetatag(void);

  void initialize(const UnicodeString &a_arguments);
  UnicodeString execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect);
public:
  enum {
    to_upper,
    to_lower,
    to_title
  } m_action;
};

} /* namespace mru */

#endif /* TEXT_CASE_TAG_HPP */

