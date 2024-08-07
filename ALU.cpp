#include <iostream>
using namespace std;
int nand(int a, int b) {
    if (a == 1 && b == 1)
        return 0;
    else
        return 1;
}
int OR(int a, int b) {
    return nand(nand(a, a), nand(b, b));
}
int AND(int a, int b) {
    return nand(nand(a, b), nand(a, b));
}
int NOT(int a) {
    return nand(a, a);
}
int NOR(int a, int b) {
    return nand(OR(a, b), OR(a, b));
}
int XOR(int a, int b) {
    return nand(nand(a, nand(a, b)), nand(b, nand(a, b)));
}
void half_adder(int a, int b, int& sum, int& carry)
{
    sum = XOR(a, b);
    carry = AND(a, b);
}

void full_adder(int a, int b, int carryin, int& output, int& carryout)
{
    int sum1, carry1, carry2;
    half_adder(a, b, sum1, carry1);
    half_adder(sum1, carryin, output, carry2);
    carryout = OR(carry1, carry2);
}

void one_bit_ALU(int a, int ena, int b, int enb, int S0, int S1, int CarryIn, int& CarryOut, int& Output)
{
    Output = 0;
    CarryOut = CarryIn;
    if (S0 == 0 && S1 == 0) {
        Output = NOT(a);
    }
    else if (S0 == 0 && S1 == 1) {
        Output = NOT(b);
    }
    else if (S0 == 1 && S1 == 0) {
        Output = XOR(a, b);
    }
    else if (S0 == 1 && S1 == 1) {

        full_adder(a, b, CarryIn, Output, CarryOut);
    }
}

void nera_operacijos()
{
    cout << "Nera operacijos.";
}

void neigiamas_skaicius(int a[], int b[], int& CarryOut, int Output[])
{
    for (int i = 0; i < 8; i++) {
        one_bit_ALU(a[i], 1, b[i], 1, 0, 1, 0, CarryOut, Output[i]);
    }
    for (int i = 0; i < 8; i++) {
        cout << Output[i];
    }
}

void palyginimas(int a[], int b[], int& CarryOut, int Output[], int F)
{
    for (int i = 0; i < 8; i++) {
        one_bit_ALU(a[i], 1, b[i], 1, 1, 0, 0, CarryOut, Output[i]);
        cout << Output[i];
    }

    cout << endl;

    F = NOR(OR(OR(Output[0], Output[1]), OR(Output[2], Output[3])), OR(OR(Output[4], Output[5]), OR(Output[6], Output[7])));
    cout << "F:" << F << endl;
}

void astuoniu_bitu_adderis(int a[], int b[], int& CarryOut, int Output[], int& Cflag)
{
    for (int i = 7; i >= 0; i--) {
        one_bit_ALU(a[i], 1, b[i], 1, 1, 1, Cflag, Cflag, Output[i]);
    }
    for (int i = 0; i < 8; i++) {
        cout << Output[i];
    }
    cout << endl;
    if (Cflag != 0) {
        cout << "Cflag: 1" << endl;
    }
    else {
        cout << "Cflag: 0" << endl;
    }

}

void daugyba(int a[], int b[], int Output[], int& Cflag) {

    for (int i = 0; i < 16; i++) {
        Output[i] = 0;
    }

    Cflag = 0;

    for (int i = 7; i >= 0; --i) {
        int carry = 0;
        for (int j = 7; j >= 0; --j) {
            int rIndex = i + j + 1;
            int temp = Output[rIndex] + a[j] * b[i] + carry;
            Output[rIndex] = temp % 2;
            carry = temp / 2;
        }

        if (carry > 0) {
            Cflag = 1;
        }
    }

    for (int i = 8; i < 16; i++) {
        cout << Output[i];
    }
    cout << endl;
    if (Cflag) {
        cout << "Overflow Cflag: 1" << endl;
    }
    else {
        cout << "Cflag: " << Cflag << endl;
    }
}

void shift_a(int a[], int size, int Cntr, int& Cflag)
{
    cout << "Iveskite Cntr: 0 - poslinkis i kaire, 1 - poslinkis i desne." << endl;
    cin >> Cntr;

    if (Cntr == 0) {
        if (a[0] == 1)
        {
            Cflag = 1;
        }
        else
        {
            Cflag = 0;
        }
        for (int i = 0; i < size - 1; ++i) {
            a[i] = a[i + 1];
        }
        a[size - 1] = 0;

    }

    else if (Cntr == 1) {
        if (a[size - 1] == 1)
        {
            Cflag = 1;
        }
        else
        {
            Cflag = 0;
        }
        for (int i = size - 1; i > 0; --i) {
            a[i] = a[i - 1];
        }
        a[0] = 0;
    }

    for (int i = 0; i < 8; i++) {
        cout << a[i];
    }
    cout << endl;
    cout << "Cflag: " << Cflag;

}


int main() {
    int a[8] = { 1,1,0,0,0,1,1,0 };
    int b[8] = { 1,0,0,0,0,1,1,1 };
    int decoder[3] = { 1, 0, 1 };

    int Output[8];
    int CarryOut = 0;
    int Cflag = 0;
    int F = 0;
    int Cntr = 0;
    int result[16] = {};


    if (decoder[0] == 0 && decoder[1] == 0 && decoder[2] == 0)
    {
        nera_operacijos();
    }
    if (decoder[0] == 0 && decoder[1] == 0 && decoder[2] == 1)
    {
        neigiamas_skaicius(a, b, CarryOut, Output);
        cout << endl;
        cout << "Cflag: " << Cflag << endl;
        cout << "F: " << F << endl;

    }
    if (decoder[0] == 0 && decoder[1] == 1 && decoder[2] == 0)
    {
        palyginimas(a, b, CarryOut, Output, F);
        cout << "Cflag: " << Cflag << endl;
    }
    if (decoder[0] == 0 && decoder[1] == 1 && decoder[2] == 1)
    {
        astuoniu_bitu_adderis(a, b, CarryOut, Output, Cflag);
        cout << "F: " << F << endl;
    }
    if (decoder[0] == 1 && decoder[1] == 0 && decoder[2] == 0)
    {
        daugyba(a, b, result, Cflag);
        cout << "F: " << F << endl;
    }
    if (decoder[0] == 1 && decoder[1] == 0 && decoder[2] == 1)
    {
        shift_a(a, 8, Cntr, Cflag);
        cout << endl;
        cout << "F: " << F << endl;
    }
    if (decoder[0] == 1 && decoder[1] == 1 && decoder[2] == 0)
    {
        nera_operacijos();
    }
    if (decoder[0] == 1 && decoder[1] == 1 && decoder[2] == 1)
    {
        nera_operacijos();
    }

    return 0;
}