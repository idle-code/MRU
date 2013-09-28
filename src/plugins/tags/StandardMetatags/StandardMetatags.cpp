#include "CountMetatag.hpp"
#include "ExtMetatag.hpp"
#include "NameMetatag.hpp"
#include "DirMetatag.hpp"
#include "TextCaseMetatag.hpp"
#include "SizeMetatag.hpp"
#include "FormatMetatag.hpp"

#include "plugins/MetatagPlugin.hpp"

METATAG_EXPORTS_START
  EXPORT_METATAG_PLUGIN_FACTORY(mru::CountMetatag, "Count")
  EXPORT_METATAG_PLUGIN_FACTORY(mru::ExtMetatag, "Ext")
  EXPORT_METATAG_PLUGIN_FACTORY(mru::NameMetatag, "Name")
  EXPORT_METATAG_PLUGIN_FACTORY(mru::DirMetatag, "Dir")
  EXPORT_METATAG_PLUGIN_FACTORY(mru::TextCaseMetatag, "TextCase")
  EXPORT_METATAG_PLUGIN_FACTORY(mru::SizeMetatag, "Size")
  EXPORT_METATAG_PLUGIN_FACTORY(mru::FormatMetatag, "Format")
METATAG_EXPORTS_END

