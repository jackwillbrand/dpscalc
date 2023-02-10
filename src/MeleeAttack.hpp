#include "AttackType.hpp"

class MeleeAttack : public AttackType
{
    public:
        int         calc_max_hit(const attacker& attacker)                                    override;
        float       calc_chance_to_hit(const attacker& attacker, const defender& defender)    override;
        virtual int calc_attack_roll(const attacker& attacker)                                override;
        virtual int calc_defence_roll(const attack_style atk_style, const defender& defender) override;
    
    private:
        int calc_effective_strength(const attacker& attacker) const;
        int calc_effective_attack(const attacker& attacker)   const;
        int sum_attack_bonus(const gear_set& gear_set)        const;
        int sum_strength_bonus(const gear_set& gear_set)      const;
};