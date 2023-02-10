#include "AttackType.hpp"

float AttackType::calc_dps(const attacker& attacker, const defender& defender)
{
    float dmg_per_hit = calc_max_hit(attacker) * calc_chance_to_hit(attacker, defender) / 2;
    result_.dps_ = dmg_per_hit / (0.6 * attacker.loadout_.weapon_.attack_speed_);
    return result_.dps_;
}
