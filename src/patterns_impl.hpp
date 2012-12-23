#ifndef PATTERNS_IMPL_HPP
#error "This is implementation file. Use patterns.hpp instead"
#else

namespace mru
{

template<typename Derived>
Derived *
custom_singleton<Derived>::m_instance = NULL;

template<typename Derived>
bool
custom_singleton<Derived>::set_instance(Derived *a_instance)
{
  if(m_instance != NULL && a_instance != NULL) {
    ERR("Singleton is already initialized");
    return false;
  }
  m_instance = a_instance;
  return true;
}

template<typename Derived>
Derived &
custom_singleton<Derived>::get_reference(void)
{
  return *m_instance;
}

template<typename Derived>
Derived *
custom_singleton<Derived>::get_instance(void)
{
  return m_instance;
}

template<typename Derived>
void
custom_singleton<Derived>::destroy_instance(void)
{
  if(m_instance != NULL) {
    delete m_instance;
    m_instance = NULL;
  }
}



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

template<typename Derived>
Derived &
singleton<Derived>::get_reference(void)
{
  if(m_instance == NULL)
    m_instance = new Derived();
  return *m_instance;
}

template<typename Derived>
void
singleton<Derived>::destroy_instance(void)
{
  if(m_instance != NULL) {
    delete m_instance;
    m_instance = NULL;
  }
}



template<typename Derived, typename ArgType1>
Derived *
singleton1<Derived, ArgType1>::m_instance = NULL;

template<typename Derived, typename ArgType1>
Derived &
singleton1<Derived, ArgType1>::get_reference(void)
{
  return *m_instance;
}

template<typename Derived, typename ArgType1>
Derived *
singleton1<Derived, ArgType1>::get_instance(void)
{
  return m_instance;
}

template<typename Derived, typename ArgType1>
Derived *
singleton1<Derived, ArgType1>::get_instance(ArgType1 a_arg1)
{
  if(m_instance == NULL)
    m_instance = new Derived(a_arg1);
  return m_instance;
}

template<typename Derived, typename ArgType1>
void
singleton1<Derived, ArgType1>::destroy_instance(void)
{
  if(m_instance != NULL) {
    delete m_instance;
    m_instance = NULL;
  }
}



template<typename Derived, typename ArgType1, typename ArgType2>
Derived *
singleton2<Derived, ArgType1, ArgType2>::m_instance = NULL;

template<typename Derived, typename ArgType1, typename ArgType2>
Derived *
singleton2<Derived, ArgType1, ArgType2>::get_instance(void)
{
  return m_instance;
}

template<typename Derived, typename ArgType1, typename ArgType2>
Derived &
singleton2<Derived, ArgType1, ArgType2>::get_reference(void)
{
  return *m_instance;
}

template<typename Derived, typename ArgType1, typename ArgType2>
Derived *
singleton2<Derived, ArgType1, ArgType2>::get_instance(ArgType1 a_arg1, ArgType2 a_arg2)
{
  if(m_instance == NULL)
    m_instance = new Derived(a_arg1, a_arg2);
  return m_instance;
}

template<typename Derived, typename ArgType1, typename ArgType2>
void
singleton2<Derived, ArgType1, ArgType2>::destroy_instance(void)
{
  if(m_instance != NULL) {
    delete m_instance;
    m_instance = NULL;
  }
}

/* ------------------------------------------------------------------------- */

template<typename Derived>
Derived *
factory_method<Derived>::create(void)
{
  return new Derived();
}

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

template<typename Object>
factory_function<Object>::factory_function(create_function_type a_create_handler, destroy_function_type a_destroy_handler)
  : m_create_function(a_create_handler), m_destroy_function(a_destroy_handler)
{ }

template<typename Object>
Object *
factory_function<Object>::create(void) const
{
  return m_create_function();
}

template<typename Object>
void
factory_function<Object>::destroy(Object *&a_object) const
{
  if(m_destroy_function != NULL)
    m_destroy_function(a_object);
  else
    delete a_object;
  a_object = NULL;
}

/* ------------------------------------------------------------------------- */

} /* namespace mru */

#endif /* PATTERNS_IMPL_HPP */

