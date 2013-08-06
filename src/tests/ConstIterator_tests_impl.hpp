#ifndef CONST_ITERATOR_TESTS_IMPL_HPP
#error "This is implementation file. Use ConstIterator_tests.hpp instead"
#else

template<typename ValueType>
void
ConstIterator_tests<ValueType>::end(void)
{
  iterator_ptr = getConstIterator(ValueList());

  CPPUNIT_ASSERT(iterator_ptr->atEnd());
}

template<typename ValueType>
void
ConstIterator_tests<ValueType>::progress(void)
{
  ValueList sample_values = getSampleValues();
  CPPUNIT_ASSERT(sample_values.size() > 0);

  iterator_ptr = getConstIterator(sample_values);
  
  CPPUNIT_ASSERT(!iterator_ptr->atEnd());

  typename ValueList::iterator i = sample_values.begin();
  for(; i != sample_values.end(); ++i) {
    CPPUNIT_ASSERT(!iterator_ptr->atEnd());
    //VAL(*i);
    CPPUNIT_ASSERT_EQUAL(*i, iterator_ptr->getCurrent());
    if(!iterator_ptr->next())
      break;
  }
  CPPUNIT_ASSERT(iterator_ptr->atEnd());
  CPPUNIT_ASSERT(i != sample_values.end());
  ++i;
  CPPUNIT_ASSERT(i == sample_values.end());
}

template<typename ValueType>
void
ConstIterator_tests<ValueType>::reset(void)
{
  ValueList sample_values = getSampleValues();
  CPPUNIT_ASSERT(sample_values.size() > 0);

  iterator_ptr = getConstIterator(sample_values);
  
  typename ValueList::iterator i = sample_values.begin();
  do {
    CPPUNIT_ASSERT(!iterator_ptr->atEnd());
    CPPUNIT_ASSERT_EQUAL(*i, iterator_ptr->getCurrent());
    ++i;
  } while(iterator_ptr->next());

  CPPUNIT_ASSERT(i == sample_values.end());
  CPPUNIT_ASSERT(iterator_ptr->atEnd());

}

#endif /* CONST_ITERATOR_TESTS_IMPL_HPP */

