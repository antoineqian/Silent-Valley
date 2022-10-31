#ifndef STATE_HPP
#define STATE_HPP

#include "../Raver.hpp"
#include <memory>
using std::shared_ptr;

class State
{
public:
    // Executes when the state is entered
    virtual void enter(shared_ptr<Raver> pRaver) = 0;
    // State's normal update function
    virtual void execute(shared_ptr<Raver> pRaver) = 0;
    // Executes when the state is exited
    virtual void exit(shared_ptr<Raver> pRaver) = 0;

    virtual ~State() {}
};

#endif