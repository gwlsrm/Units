// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <iostream>
#include <sstream>
#include <cassert>

#include "fraction.h"

Fraction::Fraction(int numerator, int denominator)
    : m_numerator(numerator), m_denominator(denominator)
{
    assert(denominator != 0 && "Division by zero");
    reduce();
}

Fraction::Fraction(const Fraction& f1)
    : m_numerator(f1.m_numerator), m_denominator(f1.m_denominator)
{
}

Fraction::~Fraction()
{
}

void Fraction::print() const
{
    using std::cout;
    cout << m_numerator << '/' << m_denominator << '\n';
}

std::string Fraction::toString() const
{
    std::ostringstream os;
    os << m_numerator << '/' << m_denominator;
    return os.str();
}

void Fraction::reduce()
{
    int a_nod = nod(m_numerator, m_denominator);
    if (a_nod > 1) {
        m_numerator /= a_nod;
        m_denominator /= a_nod;
    }
}

double Fraction::toDouble() const
{
    return static_cast<double>(m_numerator)/m_denominator;
}

std::ostream& operator<< (std::ostream &os, const Fraction &f1) {
    os << f1.m_numerator << '/' << f1.m_denominator;
    return os;
}

int Fraction::nod(int a, int b)
{
    return (b == 0) ? (a > 0 ? a : -a) : nod(b, a % b);
}


Fraction operator+(const Fraction& f1, const Fraction f2) {
    int denum = f1.m_denominator * f2.m_denominator;
    int num = f1.m_numerator*f2.m_denominator + f2.m_numerator*f1.m_denominator;
    return Fraction(num, denum);
}

Fraction operator-(const Fraction& f1, const Fraction f2) {
    int denum = f1.m_denominator * f2.m_denominator;
    int num = f1.m_numerator*f2.m_denominator - f2.m_numerator*f1.m_denominator;
    return Fraction(num, denum);
}

Fraction operator*(const Fraction& f1, const Fraction f2) {
    return Fraction(f1.m_numerator*f2.m_numerator, f1.m_denominator * f2.m_denominator);
}

Fraction operator*(const Fraction& f1, int value) {
    return Fraction(f1.m_numerator*value, f1.m_denominator);
}
Fraction operator*(int value, const Fraction& f1) {
    return Fraction(f1.m_numerator*value, f1.m_denominator);
}

Fraction operator/(const Fraction& f1, const Fraction f2) {
    int num = f1.m_numerator*f2.m_denominator;
    int denum = f1.m_denominator * f2.m_numerator;
    return Fraction(num, denum);
}

Fraction Fraction::operator-() const
{
    return Fraction(-m_numerator, m_denominator);
}

Fraction& Fraction::operator++()
{
    ++m_numerator;
    return *this;
}

Fraction& Fraction::operator--()
{
    --m_numerator;
    return *this;
}

const Fraction Fraction::operator++(int)
{
    Fraction tmp = *this;
    ++m_numerator;
    return tmp;
}

const Fraction Fraction::operator--(int)
{
    Fraction tmp = *this;
    --m_numerator;
    return tmp;
}

bool Fraction::operator!() const
{
    return (m_numerator == 0);
}

bool operator==(const Fraction &f1, const Fraction &f2) {
    return (f1.m_numerator == f2.m_numerator && f1.m_denominator == f2.m_denominator);
}

bool operator!=(const Fraction &f1, const Fraction &f2) {
    return !(f1 == f2);
}

bool operator>(const Fraction &f1, const Fraction &f2) {
    return f1.m_numerator*f2.m_denominator > f2.m_numerator*f1.m_denominator;
}

bool operator<(const Fraction &f1, const Fraction &f2) {
    return f1.m_numerator*f2.m_denominator < f2.m_numerator*f1.m_denominator;
}

bool operator>=(const Fraction &f1, const Fraction &f2) {
    return f1.m_numerator*f2.m_denominator >= f2.m_numerator*f1.m_denominator;
}

bool operator<=(const Fraction &f1, const Fraction &f2) {
    return f1.m_numerator*f2.m_denominator <= f2.m_numerator*f1.m_denominator;
}
