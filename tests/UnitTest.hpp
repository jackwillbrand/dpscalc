#ifndef UNITTEST_HPP_
#define UNITTEST_HPP_

#include <string>

class UnitTest
{
    public:
        UnitTest(const std::string& name) : name_(name) {}

        bool perform_test()
        {
            result_ = condition();
            return result_;
        }
        
        virtual bool condition() const = 0;

        bool get_result() const { return result_; }
        const std::string& get_name() const { return name_; }

    private:
        std::string           name_;
        bool                  result_;
};

#endif // UNITTEST_HPP_