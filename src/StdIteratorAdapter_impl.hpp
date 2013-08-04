#ifndef STD_ITERATOR_ADAPTER_IMPL_HPP
#error "This is implementation file. Use StdIteratorAdapter.hpp instead"
#else

namespace mru
{

template<typename ConstStdIterator>
ConstStdIteratorAdapter<ConstStdIterator>::ConstStdIteratorAdapter(const ConstStdIterator &start_iter, const ConstStdIterator &end_iter)
  : start_iterator(start_iter), end_iterator(end_iter)
{
  first();
}

template<typename ConstStdIterator>
void
ConstStdIteratorAdapter<ConstStdIterator>::first(void)
{
  current_iterator = start_iterator;
}

template<typename ConstStdIterator>
bool
ConstStdIteratorAdapter<ConstStdIterator>::next(void)
{
  assert(!atEnd());
  ++current_iterator;
  return !atEnd();
}

template<typename ConstStdIterator>
bool
ConstStdIteratorAdapter<ConstStdIterator>::atEnd(void) const
{
  return current_iterator == end_iterator;
}

template<typename ConstStdIterator>
typename ConstStdIteratorAdapter<ConstStdIterator>::ValueType
ConstStdIteratorAdapter<ConstStdIterator>::getCurrent(void) const
{
  return *current_iterator;
}

/* ------------------------------------------------------------------------- */

template<typename StdIterator>
StdIteratorAdapter<StdIterator>::StdIteratorAdapter(const StdIterator &start_iter, const StdIterator &end_iter)
  : ConstStdIteratorAdapter<StdIterator>(start_iter, end_iter)
{ }

template<typename StdIterator>
typename StdIteratorAdapter<StdIterator>::ValueType &
StdIteratorAdapter<StdIterator>::getCurrent(void)
{
  return *ConstStdIteratorAdapter<StdIterator>::current_iterator;
}

} /* namespace mru */

#endif /* STD_ITERATOR_ADAPTER_IMPL_HPP */

