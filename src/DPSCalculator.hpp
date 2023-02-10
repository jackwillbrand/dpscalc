#ifndef DPSCALCULATOR_HPP_
#define DPSCALCULATOR_HPP_

#include <vector>

#include "structures.hpp"

class DPSCalculator
{
    public:
        DPSCalculator(std::vector<attacker> attackers, std::vector<defender> defenders) : attackers_(attackers), defenders_(defenders) {}

        void calculate_all_dps();
        void print_results();

    private:
        std::vector<std::vector<Result>> results_;
        std::vector<attacker> attackers_;
        std::vector<defender> defenders_;
};

#endif // DPSCALCULATOR_HPP_