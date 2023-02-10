#include "structures.hpp"

#include <cmath>
#include <stdexcept>

class AttackType
{
    public:
        float calc_dps(const attacker& attacker, const defender& defender);

        virtual int   calc_max_hit(const attacker& attacker)                                    = 0;
        virtual float calc_chance_to_hit(const attacker& attacker, const defender& defender)    = 0;
        virtual int   calc_attack_roll(const attacker& attacker)                                = 0;
        virtual int   calc_defence_roll(const attack_style atk_style, const defender& defender) = 0;

        const Result& get_result() const { return result_; }
    
    protected:
        Result result_;
};

/*
class RangedAttack : public AttackType
{
    public:
        int calc_max_hit(const attacker& attacker) override;
        float calc_chance_to_hit(const attacker& attacker, const defender& defender) override;
    
    private:
        int sum_ranged_bonus(const gear_set& gear_set) const;
};

class MagicAttack : public AttackType
{
    public:
        int calc_max_hit(const attacker& attacker) override;
        float calc_chance_to_hit(const attacker& attacker, const defender& defender) override;
    
    private:
        float sum_magic_bonus(const gear_set& gear_set) const;
};
*/
