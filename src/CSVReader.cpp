#include "CSVReader.hpp"

#include <fstream>
#include <sstream>

bool CSVReader::read_csv()
{
    std::ifstream file(filename_);
    if (!file.is_open())
        return false;

    std::string line;
    int row = 0;
    while (std::getline(file, line))
    {
        std::istringstream row_stream(line);
        std::string cell;

        int col = 0;
        std::string key;
        CSVRow row_data;
        while (std::getline(row_stream, cell, ','))
        {
            if (row == 0)
                headers_.push_back(cell);
            else
            {
                if (col == 0)
                    key = cell;
                else
                {
                    row_data[headers_[col]] = cell;
                }
            }
            col++;
        }

        if (row != 0)
            data_[key] = row_data;
        row++;
    }
    return true;
}

void CSVReader::print_data() const
{
    for (const auto& row : data_)
    {
        print_data_at(row.first);
    }
}

void CSVReader::print_data_at(const std::string& key) const
{
    std::cout << key << ":\n";
    for (const auto& cell : data_.at(key))
        std::cout << "\t" << cell.first << ": " << cell.second << "\n";
}
    
