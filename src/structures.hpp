#ifndef STRUCTURES_HPP_
#define STRUCTURES_HPP_

#include <string>

enum attack_style
{
    stab,
    slash,
    crush,
    magic,
    range
};

struct equippable_item
{
    std::string name_;
    std::string examine_;

    int stab_atk_bonus_;
    int slash_atk_bonus_;
    int crush_atk_bonus_;
    int magic_atk_bonus_;
    int range_atk_bonus_;

    int stab_def_bonus_;
    int slash_def_bonus_;
    int crush_def_bonus_;
    int magic_def_bonus_;
    int range_def_bonus_;

    int str_bonus_;
    int rng_bonus_;
    float mag_bonus_;
    int pray_bonus_;
};

struct weapon : equippable_item
{
    int attack_speed_;
    attack_style attack_style_;
    bool special_attack_;
};

struct gear_set
{
    weapon weapon_;
    equippable_item shield_;
    equippable_item helmet_;
    equippable_item body_;
    equippable_item legs_;
    equippable_item gloves_;
    equippable_item boots_;
    equippable_item amulet_;
    equippable_item ring_;
    equippable_item cape_;
    equippable_item ammo_;
};

struct skills
{
    int attack_;
    int strength_;
    int defence_;
    int ranged_;
    int magic_;
    int prayer_;
};

enum prayer
{
    no_prayer,
    piety,
    rigour,
    augury
};

enum potion
{
    no_potion,
    super_attack,
    super_strength,
    super_defence,
    super_ranged,
    super_magic,
    smelling_salts
};

struct attacker
{
    gear_set loadout_;
    skills skills_;
    prayer prayer_;
    potion potion_;
    bool using_thrall_;
};

enum defender_type
{
    none,
    undead,
    demon,
    dragon,
    leafy,
    xerician,
    vampyre,
    kalphite,
    golem
};

struct defender
{
    defender_type type_;

    int atk_lvl_;
    int str_lvl_;
    int def_lvl_;
    int rng_lvl_;
    int mag_lvl_;

    int stab_def_;
    int slash_def_;
    int crush_def_;
    int magic_def_;
    int range_def_;
};

struct Result
{
    float dps_              = 0.0;
    int   max_hit_          = 0;
    float chance_to_hit_    = 0.0;
    int   max_attack_roll_  = 0;
    int   max_defence_roll_ = 0;
};

#endif /* STRUCTURES_HPP_ */