#ifndef UNICODE_VARTIAN_TREE
#define UNICODE_VARTIAN_TREE

#define INVALID_NAME_CHARACTERS L"\"\'[]()=:/"
#include <data_tree/text_path.hpp>
#include <data_tree/basic_variant.hpp>
#include <data_tree/basic_data_tree.hpp>
#include <string>

namespace mru
{

typedef data_tree::text_path<std::wstring> unicode_path;

} /* namespace mru */

#endif /* UNICODE_VARTIAN_TREE */

