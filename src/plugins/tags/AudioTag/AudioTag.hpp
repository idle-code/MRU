#ifndef AUDIO_TAG_HPP
#define AUDIO_TAG_HPP

#include <plugins/TagPlugin.hpp>

namespace mru
{

class AudioTag : public TagPlugin {
public:
  PLUGIN_NAME("Audio")
  AudioTag(void);
  ~AudioTag(void);

  void initialize(const UnicodeString &a_arguments);
  UnicodeString execute(const FileIterator &a_file_path, const UnicodeString &a_area_of_effect);
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

