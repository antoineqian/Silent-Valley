#include "RaverStates.hpp"
#include <random>

void GoDance::enter(shared_ptr<Raver> pRaver)
{
    std::cout << "Entered godance state\n";
    std::random_device rd;                          // obtain a random number from hardware
    std::mt19937 gen(rd());                         // seed the generator
    std::uniform_int_distribution<> distr(-96, 96); // define the range
    pRaver->setTarget({constants::window_width / 2.f + distr(gen),
                       constants::window_height / 2.f + distr(gen)});
}

void GoDance::execute(shared_ptr<Raver> pRaver)
{
    pRaver->seekTarget();
    if (pRaver->targetReached())
    {
        pRaver->setAnimation("up_dancing");
    }
}

void GoDance::exit(shared_ptr<Raver> pRaver)
{
}

shared_ptr<GoDance> GoDance::inst()
{
    static shared_ptr<GoDance> goDance;
    return goDance;
}