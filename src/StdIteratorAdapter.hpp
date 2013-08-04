#ifndef STD_ITERATOR_ADAPTER_HPP
#define STD_ITERATOR_ADAPTER_HPP

#include "Iterator.hpp"

namespace mru
{

template<typename ConstStdIterator>
class ConstStdIteratorAdapter : public ConstIterator<typename ConstStdIterator::value_type> {
public:
  typedef typename Iterator<typename ConstStdIterator::value_type>::ValueType ValueType;
public:
  ConstStdIteratorAdapter(const ConstStdIterator &start_iter, const ConstStdIterator &end_iter);

  void first(void);
  bool next(void);
  bool atEnd(void) const;

  ValueType getCurrent(void) const;

protected:
  const ConstStdIterator start_iterator;
  const ConstStdIterator end_iterator;
  ConstStdIterator current_iterator;
};

template<typename StdIterator>
class StdIteratorAdapter : public ConstStdIteratorAdapter<StdIterator>, public Iterator<typename StdIterator::value_type> {
public:
  typedef Iterator<typename StdIterator::value_type> ParentIterator;
  typedef ConstStdIteratorAdapter<StdIterator> ParentStdIteratorAdapter;
  typedef typename ParentIterator::ValueType ValueType;
public:
  StdIteratorAdapter(const StdIterator &start_iter, const StdIterator &end_iter);

  void first(void)
  {
    return ParentStdIteratorAdapter::first();
  }

  bool next(void)
  {
    return ParentStdIteratorAdapter::next();
  }

  bool atEnd(void) const
  {
    return ParentStdIteratorAdapter::atEnd();
  }

  ValueType getCurrent(void) const
  {
    return ParentStdIteratorAdapter::getCurrent();
  }

  ValueType& getCurrent(void);
};

} /* namespace mru */

#define STD_ITERATOR_ADAPTER_IMPL_HPP
#include "StdIteratorAdapter_impl.hpp"
#undef STD_ITERATOR_ADAPTER_IMPL_HPP

#endif /* STD_ITERATOR_ADAPTER_HPP */

