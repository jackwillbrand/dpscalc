#ifndef CSVREADERTEST_HPP_
#define CSVREADERTEST_HPP_

#include "UnitTest.hpp"
#include "../src/CSVReader.hpp"

bool test_monsters(const CSVReader& csv_reader);
bool test_items(const CSVReader& csv_reader);

class CSVReaderTest : public UnitTest
{
    public:
        CSVReaderTest() : UnitTest("CSVReaderTest") {}
        bool condition() const override;
};

#endif // CSVREADERTEST_HPP_