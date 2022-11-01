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

    // this is a singleton
    // unique_ptr<GoDance> inst();

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

    // this is a singleton
    // unique_ptr<Idle> inst();

    void enter(shared_ptr<Raver> pRaver) override;

    void execute(shared_ptr<Raver> pRaver) override;

    void exit(shared_ptr<Raver> pRaver) override;
};
// //------------------------------------------------------------------------
// //
// //  Entity will go to a bank and deposit any nuggets he is carrying. If the
// //  Raver is subsequently wealthy enough he'll walk home, otherwise he'll
// //  keep going to get more gold
// //------------------------------------------------------------------------
// class VisitBankAndDepositGold : public State
// {
// private:
//     VisitBankAndDepositGold() {}

//     // copy ctor and assignment should be private
//     VisitBankAndDepositGold(const VisitBankAndDepositGold &);
//     VisitBankAndDepositGold &operator=(const VisitBankAndDepositGold &);

// public:
//     // this is a singleton
//     static VisitBankAndDepositGold *Instance();

//     virtual void Enter(shared_ptr<Raver> Raver);

//     virtual void Execute(shared_ptr<Raver> Raver);

//     virtual void Exit(shared_ptr<Raver> Raver);
// };

// //------------------------------------------------------------------------
// //
// //  Raver will go home and sleep until his fatigue is decreased
// //  sufficiently
// //------------------------------------------------------------------------
// class GoHomeAndSleepTilRested : public State
// {
// private:
//     GoHomeAndSleepTilRested() {}

//     // copy ctor and assignment should be private
//     GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested &);
//     GoHomeAndSleepTilRested &operator=(const GoHomeAndSleepTilRested &);

// public:
//     // this is a singleton
//     static GoHomeAndSleepTilRested *Instance();

//     virtual void Enter(shared_ptr<Raver> Raver);

//     virtual void Execute(shared_ptr<Raver> Raver);

//     virtual void Exit(shared_ptr<Raver> Raver);
// };

// //------------------------------------------------------------------------
// //
// //------------------------------------------------------------------------
// class QuenchThirst : public State
// {
// private:
//     QuenchThirst() {}

//     // copy ctor and assignment should be private
//     QuenchThirst(const QuenchThirst &);
//     QuenchThirst &operator=(const QuenchThirst &);

// public:
//     // this is a singleton
//     static QuenchThirst *Instance();

//     virtual void Enter(shared_ptr<Raver> Raver);

//     virtual void Execute(shared_ptr<Raver> Raver);

//     virtual void Exit(shared_ptr<Raver> Raver);
// };

#endif