#ifndef METATAG_PLUGIN_CONVERTER_HPP
#define METATAG_PLUGIN_CONVERTER_HPP

#include "plugins/MetatagPlugin.hpp"
#include "MetatagBase.hpp"

namespace mru {

class MetatagPluginToMetatagFactoryConverter : public Metatag::AbstractFactory<Metatag::MetatagBase> {
public:
  static Pointer create(AbstractPluginFactory<MetatagPlugin>::Pointer plugin_factory)
  {
    return boost::make_shared<MetatagPluginToMetatagFactoryConverter>(plugin_factory);
  }

  MetatagPluginToMetatagFactoryConverter(AbstractPluginFactory<MetatagPlugin>::Pointer plugin_factory)
    : plugin_factory(plugin_factory)
  { }

  Metatag::MetatagBase::Pointer
  create(void)
  {
    return plugin_factory->createPlugin();
  }

private:
  AbstractPluginFactory<MetatagPlugin>::Pointer plugin_factory;
};

} /* namespace mru */

#endif /* METATAG_PLUGIN_CONVERTER_HPP */

