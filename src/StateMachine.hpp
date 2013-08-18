#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "Iterator.hpp"
#include <sigc++/sigc++.h>
#include <vector>
#include <set>
#include <map>
#include <stdexcept>

namespace mru
{

class StateMachineException : public std::runtime_error {
public:
  StateMachineException(const char *message) throw()
    : std::runtime_error(message)
  { }

  StateMachineException(void) throw()
    : std::runtime_error(NULL)
  { }

  ~StateMachineException(void) throw()
  { }

};

template<typename TokenType, typename Predicate = std::less<TokenType> >
class StateMachine {
public:
  //typedef sigc::signal<void> Signal;
  struct State {
    typedef sigc::signal<void, const TokenType &> Signal;
    typedef boost::shared_ptr<State> Pointer;
    Signal onEntry;
    Signal onRepeat;
    Signal onLeave;
    std::map<TokenType, State*, Predicate> transitions;

    void addTransition(const TokenType &token, State *target);
  };
public:
  StateMachine(void);
  StateMachine(typename ConstIterator<TokenType>::Pointer token_iterator);
  ~StateMachine(void);

  void setIterator(typename ConstIterator<TokenType>::Pointer token_iterator);
  typename ConstIterator<TokenType>::Pointer getIterator(void);

  void start(void);
  //Signal onStart;
  //Signal onEnd;
  //Signal onStateChange;

  State* createState(void);
  void setStartState(const State *start_state);
  void addEndState(const State *end_state);

private:
  StateMachine(const StateMachine &); //disabled
  typename ConstIterator<TokenType>::Pointer token_iterator;

  std::vector<typename State::Pointer> states;
  std::set<State*> final_states;
  State *start_state;

  typename State::Pointer getOwnState(const State *state);
};

} /* namespace mru */

#define STATE_MACHINE_IMPL_HPP
#include "StateMachine_impl.hpp"
#undef STATE_MACHINE_IMPL_HPP

#endif /* STATE_MACHINE_HPP */

