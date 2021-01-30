#include <iostream>
using namespace std;

class Credit
{
protected:
    double total;
    int monthsCount;

public:
    Credit(double total, int monthsCount) :total(total), monthsCount(monthsCount) {}
    virtual double calculate() = 0;
};

class Franc : public Credit
{
public:
    Franc(double total, int monthsCount) : Credit(total, monthsCount){}
    double calculate() override
    {
        return total / 3.5 / monthsCount;
    }
};

class Euro : public Credit
{
public:
    Euro(double total, int monthsCount) : Credit(total, monthsCount){}
    double calculate() override
    {
        return total / 4.5 / monthsCount;
    }
};

class Pln : public Credit
{
public:
    Pln(double total, int monthsCount) : Credit(total, monthsCount){}
    double calculate() override
    {
        return total / monthsCount;
    }
};

class Dolar : public Credit
{
public:
    Dolar(double total, int monthsCount) : Credit(total, monthsCount){}
    double calculate() override
    {
        return total / 3.2 / monthsCount;
    }
};

class Charge
{
    Credit* credit;
    string currency;

public:

    Charge() : credit(nullptr) {}
    string result()
    {
        if (credit == nullptr)
            return "Kredyt nie zostal ustalony!\nZle parametry!";

        return "Rata miesieczna kredytu zaciagnietego w " + currency + " wynosi " + to_string(credit->calculate()).substr(0, to_string(credit->calculate()).find('.')+3 );
    }
    void setCreditParametrs(double total, int monthsCount, string currency)
    {
        Charge::currency = currency;

        if (total <= 0 || monthsCount <= 0)
            credit = nullptr;

        else if (currency == "Franc")
            credit = new Franc(total, monthsCount);

        else if (currency == "Euro")
            credit = new Euro(total, monthsCount);

        else if (currency == "Pln")
            credit = new Pln(total, monthsCount);

        else if (currency == "Dolar")
            credit = new Dolar(total, monthsCount);

        else
            credit = nullptr;
    }
};


int main()
{
    Charge charge;

    charge.setCreditParametrs(50000, 12, "Pln");
    cout << charge.result() << endl;

    charge.setCreditParametrs(50000, 12, "Franc");
    cout << charge.result() << endl;

    charge.setCreditParametrs(50000, 12, "Euro");
    cout << charge.result() << endl;

    charge.setCreditParametrs(50000, 12, "Kolumbijskie Pesos");
    cout << charge.result() << endl;

    charge.setCreditParametrs(50000, 12, "Dolar");
    cout << charge.result() << endl;

    return 0;
}