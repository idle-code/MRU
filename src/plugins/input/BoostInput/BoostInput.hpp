#ifndef BOOST_INPUT_HPP
#define BOOST_INPUT_HPP

#include "plugins/InputPlugin.hpp"
#include <list>

namespace mru
{

class BoostInput : public InputPlugin {
public:
  FileIterator::Pointer getFileIterator(const FilePath &a_path);
};

} /* namespace mru */

#endif /* BOOST_INPUT_HPP */

