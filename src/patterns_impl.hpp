#ifndef PATTERNS_IMPL_HPP
#error "This is implementation file. Use patterns.hpp instead"
#else

namespace mru
{

template<typename Derived>
Derived *
singleton<Derived>::m_instance = NULL;

template<typename Derived>
Derived *
singleton<Derived>::get_instance(void)
{
  if(m_instance == NULL)
    m_instance = new Derived();
  return m_instance;
}

/* ------------------------------------------------------------------------- */

//template<typename Derived>
//Derived *
//factory_method<Derived>::create(void)
//{
//  return new Derived();
//}

template<typename Derived>
void
factory_method<Derived>::destroy(Derived *&a_instance)
{
  if(a_instance == NULL)
    return;
  delete a_instance;
  a_instance = NULL;
}

/* ------------------------------------------------------------------------- */

} /* namespace mru */

#endif /* PATTERNS_IMPL_HPP */
