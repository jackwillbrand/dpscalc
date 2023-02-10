#include "DPSCalculator.hpp"
#include "CSVReader.hpp"

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";

    DPSCalculator dps_calculator({}, {});
    dps_calculator.calculate_all_dps();
    std::cout << "DPS calculator created!\n";

    CSVReader csv_reader("../data/items.csv");
    if (csv_reader.read_csv())
        csv_reader.print_data();
    
    CSVReader csv_reader2("../data/monsters.csv");
    if (csv_reader2.read_csv())
        csv_reader2.print_data();

    return 0;
}