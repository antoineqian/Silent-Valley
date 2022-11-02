#ifndef RAVER_STATES_H
#define RAVER_STATES_H
#include "State.hpp"
#include <memory>
using std::make_unique;
using std::unique_ptr;

class Raver;

//------------------------------------------------------------------------
//
// Go to the dancefloor and dance
//------------------------------------------------------------------------
class GoDance : public State
{
public:
    GoDance();
    GoDance(const GoDance &) = delete;
    GoDance &operator=(const GoDance &) = delete;
    GoDance(GoDance &&) = delete;
    GoDance &operator=(GoDance &&) = delete;

    void enter(shared_ptr<Raver> pRaver) override;

    void execute(shared_ptr<Raver> pRaver) override;

    void exit(shared_ptr<Raver> pRaver) override;
};

class Idle : public State
{
public:
    Idle();
    Idle(const Idle &) = delete;
    Idle &operator=(const Idle &) = delete;
    Idle(Idle &&) = delete;
    Idle &operator=(Idle &&) = delete;

    void enter(shared_ptr<Raver> pRaver) override;

    void execute(shared_ptr<Raver> pRaver) override;

    void exit(shared_ptr<Raver> pRaver) override;
};

#endif