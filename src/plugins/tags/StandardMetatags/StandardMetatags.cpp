#include "CountMetatag.hpp"
#include "ExtMetatag.hpp"
#include "NameMetatag.hpp"
#include "DirMetatag.hpp"
#include "TextCaseMetatag.hpp"

#include "plugins/MetatagPlugin.hpp"

METATAG_EXPORTS_START
  EXPORT_METATAG_PLUGIN_FACTORY(mru::CountMetatag::Factory::create())
  EXPORT_METATAG_PLUGIN_FACTORY(mru::ExtMetatag::Factory::create())
  EXPORT_METATAG_PLUGIN_FACTORY(mru::NameMetatag::Factory::create())
  EXPORT_METATAG_PLUGIN_FACTORY(mru::DirMetatag::Factory::create())
  EXPORT_METATAG_PLUGIN_FACTORY(mru::TextCaseMetatag::Factory::create())
METATAG_EXPORTS_END

