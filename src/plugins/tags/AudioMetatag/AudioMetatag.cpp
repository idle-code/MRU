#include "AudioMetatag.hpp"
#include <taglib/taglib.h>
#include <taglib/tstring.h>
#include <taglib/fileref.h>

namespace mru
{

template<> inline
UnicodeString
glue_cast<UnicodeString, TagLib::String>(const TagLib::String &a_value)
{
  return glue_cast<UnicodeString>(a_value.toWString());
}

AudioMetatag::AudioMetatag(void)
  : MetatagPlugin(static_implementation_name())
{ }

AudioMetatag::~AudioMetatag(void)
{ }

void
AudioMetatag::initialize(const UnicodeString &a_arguments)
{
  //FO("AudioMetatag::initialize(const UnicodeString &a_arguments)");

  if(a_arguments == glue_cast<UnicodeString>("artist"))
    m_action = artist;
  else if(a_arguments == glue_cast<UnicodeString>("title"))
    m_action = title;
  else if(a_arguments == glue_cast<UnicodeString>("album"))
    m_action = album;
  else if(a_arguments == glue_cast<UnicodeString>("year"))
    m_action = year;
  else if(a_arguments == glue_cast<UnicodeString>("comment"))
    m_action = comment;
  else
    throw MetatagException(getName(), glue_cast<UnicodeString>("Unsupported argument: ") + a_arguments);
}

UnicodeString
AudioMetatag::execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect)
{
  //FO("AudioMetatag::execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect)");
  TagLib::FileRef file(a_file_path.getCurrent().string().c_str());
  if(file.isNull())
    throw MetatagException(getName(), glue_cast<UnicodeString>("Metadata not found - bad file type?"));

  switch(m_action) {
    case artist:
      if(file.tag()->artist() == TagLib::String::null)
        throw MetatagException(getName(), glue_cast<UnicodeString>("No artist tag defined in file"));
      return glue_cast<UnicodeString>(file.tag()->artist());
    case title:
      if(file.tag()->title() == TagLib::String::null)
        throw MetatagException(getName(), glue_cast<UnicodeString>("No title tag defined in file"));
      return glue_cast<UnicodeString>(file.tag()->title());
    case album:
      if(file.tag()->album() == TagLib::String::null)
        throw MetatagException(getName(), glue_cast<UnicodeString>("No album tag defined in file"));
      return glue_cast<UnicodeString>(file.tag()->album());
    case year:
      if(file.tag()->year() == 0)
        throw MetatagException(getName(), glue_cast<UnicodeString>("No year tag defined in file"));
      return glue_cast<UnicodeString>((int)file.tag()->year());
    case comment:
      if(file.tag()->comment() == TagLib::String::null)
        throw MetatagException(getName(), glue_cast<UnicodeString>("No comment tag defined in file"));
      return glue_cast<UnicodeString>(file.tag()->comment());
    default:
      throw MetatagException(getName(), glue_cast<UnicodeString>("Unsupported action: ") + glue_cast<UnicodeString>((int)m_action));
  }
  return UnicodeString();
}

} /* getNamespace mru */

EXPORT_START
  EXPORT_PLUGIN(mru::AudioMetatag)
EXPORT_END

