#include "DPSCalculator.hpp"
#include "MeleeAttack.hpp"

#include <iostream>
#include <memory>

void DPSCalculator::calculate_all_dps()
{
    for (auto& attacker : attackers_)
    {
        std::vector<Result> results;
        for (auto& defender : defenders_)
        {
            std::unique_ptr<AttackType> attack = nullptr;
            switch (attacker.loadout_.weapon_.attack_style_)
            {
                case attack_style::stab:
                case attack_style::slash:
                case attack_style::crush:
                    attack = std::make_unique<MeleeAttack>();
                    break;
                case attack_style::range:
                    //attack = std::make_unique<RangedAttack>();
                    break;
                case attack_style::magic:
                    //attack = std::make_unique<MagicAttack>();
                    break;
                default:
                    throw std::invalid_argument("Invalid attack style");
            }
            attack->calc_dps(attacker, defender);
            results.push_back(attack->get_result());
        }
        results_.push_back(results);
    }
}

void DPSCalculator::print_results()
{
    for (size_t i = 0; i < attackers_.size(); i++)
    {
        for (size_t j = 0; j < defenders_.size(); j++)
        {
            std::cout << i << " vs " << j << std::endl;
            std::cout << "DPS: " << results_[i][j].dps_ << std::endl;
            std::cout << "Max hit: " << results_[i][j].max_hit_ << std::endl;
            std::cout << "Max attack roll: " << results_[i][j].max_attack_roll_ << std::endl;
            std::cout << "Max defence roll: " << results_[i][j].max_defence_roll_ << std::endl;
            std::cout << "Chance to hit: " << results_[i][j].chance_to_hit_ << std::endl;
            std::cout << std::endl;
        }
    }
}