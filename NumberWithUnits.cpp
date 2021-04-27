#include "NumberWithUnits.hpp"
#include <iostream>
#include <map>
#include <iomanip>
#include <fstream>
using namespace std;

const double eps = 0.001;


namespace ariel {
    static map <string,map <string,double>> tab;

    NumberWithUnits::NumberWithUnits(double amount, const string& unit){
        if(tab.count(unit) == 0) {
            throw invalid_argument{"Error in the unit"};
        }
        this ->amount = amount;
        this-> unit = unit;
    }

    double convertUnit (double amount, const string& src , const string& dest) {
        if (src == dest) {
            return amount;
        }
        try {
            return amount * (tab.at(src).at(dest));
        }
        catch (const exception& exe) {
            throw invalid_argument{"Cannot convert units"};
        }
    }


    int compare(const NumberWithUnits& n1,const NumberWithUnits& n2) {
        double val = n1.amount - convertUnit(n2.amount, n2.unit,n1.unit);
        int check = 0;
        if (val > eps) {
            check = 1;
        }
        else if (-val > eps) {
            check = -1;
        }
        return check;
    }



    void NumberWithUnits::read_units(ifstream& units_file) {
        string read,u1,u2;
        double x = 0;
        double y = 0;

        while (units_file >> x >> u1 >> read >> y >> u2) {
            tab[u1][u2] = y;
            tab[u2][u1] = 1/y;

            for (auto &umap : tab[u2]) {
                double val = tab[u1][u2] * umap.second;
                tab[u1][umap.first] = val;
                tab[umap.first][u1] = 1/val; 
            }

             for (auto &umap : tab[u1]) {
                double val = tab[u2][u1] * umap.second;
                tab[u2][umap.first] = val;
                tab[umap.first][u2] = 1/val; 
            }
        }
    }

    ostream& operator<<(ostream& output ,const NumberWithUnits& n) {
        output << n.amount << "[" << n.unit << "]";
        return output;
    }

     istream& operator>>(istream& input ,NumberWithUnits& n) {
         string str;
         input >> n.amount >> str >> n.unit;
         return input;   
    }


    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& n) {
        double val = convertUnit(n.amount,n.unit,this->unit);
        NumberWithUnits op(this->amount+val,this->unit);
        return op;
    }

    NumberWithUnits NumberWithUnits::operator+() {
        NumberWithUnits op(this->amount,this->unit);
        return op;
    }

     NumberWithUnits NumberWithUnits::operator+=(const NumberWithUnits& n) {
        this->amount += convertUnit(n.amount,n.unit,this->unit);
        return *this;
    }

     NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& n) {
        double val = convertUnit(n.amount,n.unit,this->unit);
        NumberWithUnits op(this->amount-val,this->unit);
        return op;
    }

     NumberWithUnits NumberWithUnits::operator-() {
        NumberWithUnits op(-this->amount,this->unit);
        return op;
    }

    NumberWithUnits NumberWithUnits::operator-=(const NumberWithUnits& n) {
        this->amount -= convertUnit(n.amount,n.unit,this->unit);
        return *this;
    }


    NumberWithUnits NumberWithUnits::operator++() {
        ++(this->amount);
        return *this;
    }

     NumberWithUnits NumberWithUnits::operator++(int) {
        return NumberWithUnits((this->amount)++,this->unit);
    }

     NumberWithUnits NumberWithUnits::operator--() {
        --(this->amount);
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int) {
        return NumberWithUnits((this->amount)--,this->unit);
    }

    NumberWithUnits operator*(NumberWithUnits& n1, double n2) {
        return NumberWithUnits(n1.amount*n2,n1.unit);
    }

    NumberWithUnits operator*( double n2,NumberWithUnits& n1) {
        return NumberWithUnits(n1.amount*n2,n1.unit);
    }

     NumberWithUnits& NumberWithUnits::operator*=( double n) {
        this->amount *= n;
        return *this;
    }

    bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2) {
        return compare (n1,n2) < 0;
    }

    bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2) {
        return compare (n1,n2) > 0;
    }

    bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2) {
        return compare (n1,n2) <= 0;
    }

    bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2) {
        return compare (n1,n2) >= 0;
    }

    bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2) {
        return compare (n1,n2) == 0;
    }

    bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2) {
        return compare (n1,n2) != 0;
    }
}
