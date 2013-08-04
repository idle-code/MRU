#include "FileIterator.hpp"
#include "glue.hpp"
#include "make_relative_fix.hpp"
#undef NDEBUG_L
#include <debug_l.h>

namespace mru
{

FileIteratorDecorator::FileIteratorDecorator(FileIterator::Pointer instance)
  : instance(instance)
{ }

FilePath
FileIteratorDecorator::getCurrent(void) const
{
  assert(instance);
  return instance->getCurrent();
}

void
FileIteratorDecorator::first(void)
{
  assert(instance);
  instance->first();
}

bool
FileIteratorDecorator::next(void)
{
  assert(instance);
  return instance->next();
}

bool
FileIteratorDecorator::atEnd(void) const
{
  assert(instance);
  return instance->atEnd();
}

} /* namespace mru */

