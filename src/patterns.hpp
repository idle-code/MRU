#ifndef PATTERNS_HPP
#define PATTERNS_HPP

namespace mru
{

template<typename Derived>
class singleton {
public:
  static Derived* get_instance(void);
  //FIXME: add method to destroy an instance?
private:
  static Derived *m_instance;  
};

/* ------------------------------------------------------------------------- */

template<typename Derived>
class factory_method {
public:
  virtual Derived* create(void) = 0;
  virtual void destroy(Derived *&a_instance);
};

/* ------------------------------------------------------------------------- */

} /* namespace mru */

#define PATTERNS_IMPL_HPP
#include "patterns_impl.hpp"
#undef PATTERNS_IMPL_HPP

#endif /* PATTERNS_HPP */

