#include "FileIterator.hpp"
#include "glue.hpp"
#include "make_relative_fix.hpp"
#undef NDEBUG_L
#include <debug_l.h>

namespace mru
{

FileIterator::~FileIterator(void)
{ } 

/* ------------------------------------------------------------------------- */

FileIteratorDecorator::FileIteratorDecorator(FileIterator::Pointer a_instance)
  : m_instance(a_instance)
{ }

FilePath FileIteratorDecorator::getFilePath(void) const
{
  assert(m_instance);
  return m_instance->getFilePath();
}

void
FileIteratorDecorator::first(void)
{
  assert(m_instance);
  m_instance->first();
}

bool
FileIteratorDecorator::next(void)
{
  assert(m_instance);
  return m_instance->next();
}

bool
FileIteratorDecorator::atEnd(void) const
{
  assert(m_instance);
  return m_instance->atEnd();
}

} /* namespace mru */

