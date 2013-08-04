#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <boost/shared_ptr.hpp>

namespace mru 
{

template<typename ValueT>
class ConstIterator {
public:
  typedef ValueT ValueType;
  typedef boost::shared_ptr<ConstIterator<ValueType> > Pointer;
public:
  virtual ~ConstIterator(void) { }

  virtual void first(void) = 0;
  virtual bool next(void) = 0;
  virtual bool atEnd(void) const = 0;

  virtual ValueType getCurrent(void) const = 0;

  ValueType operator*(void) const
  {
    return getCurrent();
  }
};

template<typename ValueT>
class Iterator : public ConstIterator<ValueT> {
public:
  typedef ValueT ValueType;
  typedef boost::shared_ptr<Iterator<ValueType> > Pointer;
public:
  virtual ~Iterator(void) { }

  virtual ValueType& getCurrent(void) = 0;

  ValueType& operator*(void)
  {
    return getCurrent();
  }
};

} /* namespace mru */

#endif /* ITERATOR_HPP */

