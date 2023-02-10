#ifndef CSVREADER_HPP_
#define CSVREADER_HPP_

#include <iostream>
#include <string>
#include <map>
#include <vector>

typedef std::map<std::string, std::map<std::string, std::string>> CSVData;

class CSVReader
{
    public:
        CSVReader(const std::string& filename) : filename_(filename) {}
        const std::map<std::string, std::string>& operator[](const std::string& key) const { return data_.at(key); }

        bool read_csv();
        const CSVData& get_data() const { return data_; }

        void print_data() const;
        void print_data_at(const std::string& key) const;

    private:
        std::string              filename_;
        std::vector<std::string> headers_;
        CSVData                  data_;
};

#endif // CSVREADER_HPP_