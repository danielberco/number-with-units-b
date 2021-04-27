#include <iostream>
#include <map>
#include <string>

namespace ariel {
    class NumberWithUnits {
        private :
        std::string unit;
        double amount;

        

    public :
       static void read_units(std::ifstream& units_file);
       NumberWithUnits(double am, const std::string& unit);
       ~NumberWithUnits(){}
       friend int compare(const NumberWithUnits& x,const NumberWithUnits& y);

        NumberWithUnits operator+(const NumberWithUnits& n1);
        NumberWithUnits operator+();
        NumberWithUnits operator+=(const NumberWithUnits& n1);
        NumberWithUnits operator-(const NumberWithUnits& n1);
        NumberWithUnits operator-();
        NumberWithUnits operator-=(const NumberWithUnits& n1);
        NumberWithUnits operator++();
        NumberWithUnits operator++(int);
        NumberWithUnits operator--();
        NumberWithUnits operator--(int);

       friend NumberWithUnits operator*(NumberWithUnits& n1,double n2);
       friend NumberWithUnits operator*(double n2,NumberWithUnits& n1);
       NumberWithUnits& operator*=(double n);

       friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2);
       friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2);
       friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2);
       friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2);
       friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2);
       friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2);


       friend std::ostream& operator<<(std::ostream& os, const NumberWithUnits& n);
       friend std::istream& operator>>(std::istream& is, NumberWithUnits& n);

    };
}
