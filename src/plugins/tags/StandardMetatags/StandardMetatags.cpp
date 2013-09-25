#include "CountMetatag.hpp"
#include "ExtMetatag.hpp"
#include "NameMetatag.hpp"
#include "DirMetatag.hpp"
#include "TextCaseMetatag.hpp"

#include "plugins/MetatagPlugin.hpp"

METATAG_EXPORTS_START
  EXPORT_METATAG_PLUGIN_FACTORY(mru::CountMetatag, "Count")
  EXPORT_METATAG_PLUGIN_FACTORY(mru::ExtMetatag, "Ext")
  EXPORT_METATAG_PLUGIN_FACTORY(mru::NameMetatag, "Name")
  EXPORT_METATAG_PLUGIN_FACTORY(mru::DirMetatag, "Dir")
  EXPORT_METATAG_PLUGIN_FACTORY(mru::TextCaseMetatag, "TextCase")
METATAG_EXPORTS_END

