#include "MeleeAttack.hpp"

int MeleeAttack::calc_effective_strength(const attacker& attacker) const
{
    int effective_strength = attacker.skills_.strength_;
    switch (attacker.potion_)
    {
        case super_strength:
            effective_strength += 5 + (attacker.skills_.strength_ * 0.15); break;
        case smelling_salts:
            effective_strength += 11 + (attacker.skills_.strength_ * 0.16); break;
    }
    
    if (attacker.prayer_ == piety)
        effective_strength = std::floor(effective_strength * 1.23);
    
    effective_strength += 3 + 8; // aggressive style +3

    if (attacker.loadout_.weapon_.name_ ==  "Void melee helm"  &&
        (attacker.loadout_.weapon_.name_ == "Void knight top"  || attacker.loadout_.body_.name_ == "Elite void top")  &&
        (attacker.loadout_.weapon_.name_ == "Void knight robe" || attacker.loadout_.legs_.name_ == "Elite void robe") && 
        attacker.loadout_.weapon_.name_ == "Void knight gloves")
    {
        effective_strength = std::floor(effective_strength * 1.10);
    }
    
    return effective_strength;
}

int MeleeAttack::sum_attack_bonus(const gear_set& gear_set) const
{
    switch (gear_set.weapon_.attack_style_)
    {
        case stab:  return gear_set.weapon_.stab_atk_bonus_  + gear_set.shield_.stab_atk_bonus_  + gear_set.helmet_.stab_atk_bonus_  + gear_set.body_.stab_atk_bonus_   + 
                             gear_set.legs_.stab_atk_bonus_  + gear_set.gloves_.stab_atk_bonus_  + gear_set.boots_.stab_atk_bonus_  + gear_set.amulet_.stab_atk_bonus_  + 
                             gear_set.ring_.stab_atk_bonus_  + gear_set.cape_.stab_atk_bonus_   + gear_set.ammo_.stab_atk_bonus_;
        case slash: return gear_set.weapon_.slash_atk_bonus_ + gear_set.shield_.slash_atk_bonus_ + gear_set.helmet_.slash_atk_bonus_ + gear_set.body_.slash_atk_bonus_  + 
                             gear_set.legs_.slash_atk_bonus_ + gear_set.gloves_.slash_atk_bonus_ + gear_set.boots_.slash_atk_bonus_ + gear_set.amulet_.slash_atk_bonus_ + 
                             gear_set.ring_.slash_atk_bonus_ + gear_set.cape_.slash_atk_bonus_   + gear_set.ammo_.slash_atk_bonus_;
        case crush: return gear_set.weapon_.crush_atk_bonus_ + gear_set.shield_.crush_atk_bonus_ + gear_set.helmet_.crush_atk_bonus_ + gear_set.body_.crush_atk_bonus_  + 
                             gear_set.legs_.crush_atk_bonus_ + gear_set.gloves_.crush_atk_bonus_ + gear_set.boots_.crush_atk_bonus_ + gear_set.amulet_.crush_atk_bonus_ + 
                             gear_set.ring_.crush_atk_bonus_ + gear_set.cape_.crush_atk_bonus_   + gear_set.ammo_.crush_atk_bonus_;
        case range:
        case magic:
            throw std::runtime_error("Invalid attack style for melee attack.");
    }
    return 0;
}

int MeleeAttack::sum_strength_bonus(const gear_set& gear_set) const
{
    return gear_set.weapon_.str_bonus_ + gear_set.shield_.str_bonus_ + gear_set.helmet_.str_bonus_ + gear_set.body_.str_bonus_   + 
           gear_set.legs_.str_bonus_   + gear_set.gloves_.str_bonus_ + gear_set.boots_.str_bonus_  + gear_set.amulet_.str_bonus_ + 
           gear_set.ring_.str_bonus_   + gear_set.cape_.str_bonus_   + gear_set.ammo_.str_bonus_;
}

int MeleeAttack::calc_max_hit(const attacker& attacker)
{
    int effective_strength = calc_effective_strength(attacker);
    effective_strength *= sum_strength_bonus(attacker.loadout_) + 64;
    effective_strength = std::floor((effective_strength + 320) / 640.0);
    
    float gear_bonus = 1.0;
    if (attacker.loadout_.weapon_.name_ == "Slayer helmet (i)" ||
        attacker.loadout_.weapon_.name_ == "Slayer helmet"     || 
        attacker.loadout_.amulet_.name_ == "Salve amulet")
    {
        gear_bonus = 7.0 / 6.0;
    }
    if (attacker.loadout_.amulet_.name_ == "Salve amulet (ei)")
    {
        gear_bonus = 1.2;
    }

    result_.max_hit_ = std::floor(effective_strength * gear_bonus);
    return result_.max_hit_;
}

int MeleeAttack::calc_effective_attack(const attacker& attacker) const
{
    int effective_attack = attacker.skills_.attack_;
    switch (attacker.potion_)
    {
        case super_attack:
            effective_attack += 5 + (attacker.skills_.attack_ * 0.15); break;
        case smelling_salts:
            effective_attack += 11 + (attacker.skills_.attack_ * 0.16); break;
    }
    
    if (attacker.prayer_ == piety)
        effective_attack = std::floor(effective_attack * 1.20);
    
    effective_attack += 3 + 8; // aggressive style +3

    if (attacker.loadout_.weapon_.name_ ==  "Void melee helm"  &&
        (attacker.loadout_.weapon_.name_ == "Void knight top"  || attacker.loadout_.body_.name_ == "Elite void top")  &&
        (attacker.loadout_.weapon_.name_ == "Void knight robe" || attacker.loadout_.legs_.name_ == "Elite void robe") && 
        attacker.loadout_.weapon_.name_ == "Void knight gloves")
    {
        effective_attack = std::floor(effective_attack * 1.10);
    }
    
    return effective_attack;
}

int MeleeAttack::calc_attack_roll(const attacker& attacker)
{
    int attack_roll = calc_effective_attack(attacker);
    attack_roll *= sum_attack_bonus(attacker.loadout_) + 64;

    float gear_bonus = 1.0;
    if (attacker.loadout_.weapon_.name_ == "Slayer helmet (i)" ||
        attacker.loadout_.weapon_.name_ == "Slayer helmet"     || 
        attacker.loadout_.amulet_.name_ == "Salve amulet")
    {
        gear_bonus = 7.0 / 6.0;
    }
    if (attacker.loadout_.amulet_.name_ == "Salve amulet (ei)")
    {
        gear_bonus = 1.2;
    }

    result_.max_attack_roll_ = std::floor(attack_roll * gear_bonus);
    return result_.max_attack_roll_;
}

int MeleeAttack::calc_defence_roll(const attack_style atk_style, const defender& defender)
{
    int defence_roll = defender.def_lvl_ + 9;
    
    int attack_style_bonus = 0;
    switch (atk_style)
    {
        case stab:  attack_style_bonus = defender.stab_def_; break;
        case slash: attack_style_bonus = defender.slash_def_; break;
        case crush: attack_style_bonus = defender.crush_def_; break;

        case range:
        case magic:
            throw std::runtime_error("Invalid attack style for melee attack.");
    }

    result_.max_defence_roll_ = std::floor(defence_roll * (attack_style_bonus + 64.0));
    return result_.max_defence_roll_;
}

float MeleeAttack::calc_chance_to_hit(const attacker& attacker, const defender& defender)
{
    int attack_roll = calc_attack_roll(attacker);
    int defence_roll = calc_defence_roll(attacker.loadout_.weapon_.attack_style_, defender);

    if (attack_roll > defence_roll)
    {
        float numerator = defence_roll + 2;
        float denominator = 2 * (attack_roll + 1);
        result_.chance_to_hit_ = 1 - (numerator / denominator);
    }
    else
    {
        float numerator = attack_roll;
        float denominator = 2 * (defence_roll + 1);
        result_.chance_to_hit_ = numerator / denominator;
    }

    return result_.chance_to_hit_;
}