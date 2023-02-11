#include "CSVReaderTest.hpp"

#include <memory>

bool test_monsters(const CSVReader& csv_reader)
{
    std::unique_ptr<CSVRow> csv_zombie = std::make_unique<CSVRow>(csv_reader["Zombie"]);\
    if (csv_zombie == nullptr)
    {
        std::cerr << "Failed to find Zombie in monsters.csv.\n";
        return false;
    }

    if (std::stoi(csv_zombie->at("hitpoints")) != 54)
    {
        std::cerr << "Expected Zombie hp of 54, got " << csv_zombie->at("hitpoints") << ".\n";
        return false;
    }

    if (std::stoi(csv_zombie->at("magic_level")) != 1)
    {
        std::cerr << "Expected Zombie magic of 1, got " << csv_zombie->at("magic_level") << ".\n";
        return false;
    }
    
    if (std::stoi(csv_zombie->at("attack_level")) != 160)
    {
        std::cerr << "Expected Zombie attack of 160, got " << csv_zombie->at("attack_level") << ".\n";
        return false;
    }

    if (std::stoi(csv_zombie->at("defence_level")) != 62)
    {
        std::cerr << "Expected Zombie defence of 62, got " << csv_zombie->at("defence_level") << ".\n";
        return false;
    }

    if (std::stoi(csv_zombie->at("strength_level")) != 1)
    {
        std::cerr << "Expected Zombie strength of 1, got " << csv_zombie->at("strength_level") << ".\n";
        return false;  
    }

    std::unique_ptr<CSVRow> csv_dragon = std::make_unique<CSVRow>(csv_reader["Adamant dragon"]);
    if (csv_dragon == nullptr)
    {
        std::cerr << "Failed to find Adamant dragon in monsters.csv.\n";
        return false;
    }

    return true;
}

bool test_items(const CSVReader& csv_reader)
{
    std::unique_ptr<CSVRow> csv_item = std::make_unique<CSVRow>(csv_reader["Slayer cape"]);
    if (csv_item == nullptr)
    {
        std::cerr << "Failed to find Slayer cape in items.csv.\n";
        return false;
    }

    if (csv_item->at("equipable_weapon") != "False")
    {
        std::cerr << "Expected Slayer cape to not be equipable as a weapon, got " << csv_item->at("equipable_weapon") << ".\n";
        return false;
    }

    if (csv_item->at("attack_stab") != "0")
    {
        std::cerr << "Expected Slayer cape to have 0 stab attack, got " << csv_item->at("attack_stab") << ".\n";
        return false;
    }

    if (csv_item->at("attack_slash") != "0")
    {
        std::cerr << "Expected Slayer cape to have 0 slash attack, got " << csv_item->at("attack_slash") << ".\n";
        return false;
    }

    if (csv_item->at("attack_crush") != "0")
    {
        std::cerr << "Expected Slayer cape to have 0 crush attack, got " << csv_item->at("attack_crush") << ".\n";
        return false;
    }

    if (csv_item->at("defence_stab") != "9")
    {
        std::cerr << "Expected Slayer cape to have 9 stab defence, got " << csv_item->at("defence_stab") << ".\n";
        return false;
    }

    if (csv_item->at("defence_slash") != "9")
    {
        std::cerr << "Expected Slayer cape to have 9 slash defence, got " << csv_item->at("defence_slash") << ".\n";
        return false;
    }

    if (csv_item->at("defence_crush") != "9")
    {
        std::cerr << "Expected Slayer cape to have 9 crush defence, got " << csv_item->at("defence_crush") << ".\n";
        return false;
    }

    return true;
}

bool CSVReaderTest::condition() const
{
    CSVReader csv_reader("../data/items.csv");
    if (!csv_reader.read_csv())
    {
        std::cout << "Failed to read items.csv!\n";
        return false;
    }

    CSVReader csv_reader2("../data/monsters.csv");
    if (!csv_reader2.read_csv())
    {
        std::cout << "Failed to read monsters.csv!\n";
        return false;
    }

    return test_items(csv_reader) && test_monsters(csv_reader2);
}