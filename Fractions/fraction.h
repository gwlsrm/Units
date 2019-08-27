#ifndef FRACTION_H
#define FRACTION_H

#include <string>

class Fraction
{
    public:
        Fraction(int numerator=0, int denominator=1);
        Fraction(const Fraction &f1);
        virtual ~Fraction();
        // output functions
        void print() const;
        std::string toString() const;
        double toDouble() const;
        friend std::ostream& operator<< (std::ostream &os, const Fraction &f1);
        // arithmetic binary operators
        friend Fraction operator+(const Fraction& f1, const Fraction f2);
        friend Fraction operator-(const Fraction& f1, const Fraction f2);
        friend Fraction operator*(const Fraction& f1, const Fraction f2);
        friend Fraction operator*(const Fraction& f1, int value);
        friend Fraction operator*(int value, const Fraction& f1);
        friend Fraction operator/(const Fraction& f1, const Fraction f2);
        // arithmetic unary operators
        operator double() {return m_numerator/m_denominator;};
        Fraction operator-() const;
        Fraction& operator++();
        Fraction& operator--();
        const Fraction operator++(int);
        const Fraction operator--(int);
        // boolean and compare operators
        operator bool() {return m_numerator != 0;};
        bool operator!() const;
        friend bool operator==(const Fraction &f1, const Fraction &f2);
        friend bool operator!=(const Fraction &f1, const Fraction &f2);
        friend bool operator>(const Fraction &f1, const Fraction &f2);
        friend bool operator<(const Fraction &f1, const Fraction &f2);
        friend bool operator>=(const Fraction &f1, const Fraction &f2);
        friend bool operator<=(const Fraction &f1, const Fraction &f2);
    private:
        int m_numerator;
        int m_denominator;
        void reduce();
        static int nod(int a, int b);
};

#endif // FRACTION_H
