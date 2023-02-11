#include "DPSCalculator.hpp"
#include "../tests/CSVReaderTest.hpp"
#include "CSVReader.hpp"

#include <vector>
#include <memory>

#include <iostream>

int do_unit_tests()
{

    // UNIT TESTING AND DEBUGGING HERE
    // TODO: MOVE TO SEPARATE LOCATION WITH OWN CMAKE FILE
    std::vector<std::unique_ptr<UnitTest>> unit_tests;
    unit_tests.push_back(std::make_unique<CSVReaderTest>());

    int fails, passes = 0;
    std::cout << "\nRUNNING UNIT TESTS...\n";
    for (const auto& unit_test : unit_tests)
    {
        if (!unit_test->condition())
        {
            std::cout << "Unit test failed: " << unit_test->get_name() << "\n";
            fails++;
            continue;
        }
        std::cout << "Unit test passed: " << unit_test->get_name() << "\n";
        passes++;
    }

    std::cout << "Unit tests passed: " << passes << "\n";
    std::cout << "Unit tests failed: " << fails << "\n";
    std::cout << "UNIT TESTS COMPLETE\n";
    return 0;
}

int main()
{
    std::cout << "Hello World!\n";

    DPSCalculator dps_calculator({}, {});
    dps_calculator.calculate_all_dps();
    std::cout << "DPS calculator created!\n";

    return do_unit_tests();
}