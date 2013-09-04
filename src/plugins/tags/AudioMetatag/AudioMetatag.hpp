#ifndef AUDIO_TAG_HPP
#define AUDIO_TAG_HPP

#include <plugins/MetatagPlugin.hpp>

namespace mru
{

class AudioMetatag : public MetatagPlugin {
public:
  PLUGIN_FACTORY(AudioMetatag, MetatagPlugin, "Audio");

  void initialize(const UnicodeString &a_arguments);
  UnicodeString execute(const FileIterator::Pointer a_file_path, const UnicodeString &a_area_of_effect);
public:
  enum {
    artist,
    title,
    album,
    year,
    comment
  } m_action;
};

} /* namespace mru */

#endif /* AUDIO_TAG_HPP */

