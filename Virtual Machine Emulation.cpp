#include <iostream>
#include <fstream>
using namespace std;
int main() {
    char reg[16] = { 0 };
    char memory[256] = { 0 };
    char flag = 0b00000010;
    char* program_count = memory;

    ifstream fd;
    fd.open("decryptor.bin", ios::in | ios::binary);
    while (fd.get(memory[memory[255]]))
    {
        memory[255]++;
    }
    fd.close();
    fd.open("q1_encr.txt");

    while (*program_count != 0x0B) // Infinite loopa kol pc nebus 0x0B
    {
        if (*program_count == 0x01) //Rx padidinamas vienetu
        {
            reg[*(program_count + 1) & 0x0F]++;
            if (reg[*(program_count + 1) & 0x0F] == 0)
                flag = flag | 0b00001000;
            else
                flag = flag & 0b11110111;
            program_count = program_count + 2;
        }
        else if (*program_count == 0x02) //Rx sumazinamas vienetu
        {
            reg[*(program_count + 1) & 0x0F]--;
            if (reg[*(program_count + 1) & 0x0F] == 0)
                flag = flag | 0b00001000;
            else
                flag = flag & 0b11110111;
            program_count = program_count + 2;
        }
        else if (*program_count == 0x03) //Ry turinys kopijuojamas i Rx
        {
            reg[*(program_count + 1) & 0x0F] = reg[*(program_count + 1) >> 4];
            if (reg[*(program_count + 1) & 0x0F] == 0)
                flag = flag | 0b00001000;
            else
                flag = flag & 0b11110111;
            program_count = program_count + 2;
        }
        else if (*program_count == 0x04) //Baito konstanta kopojuojama i R0
        {
            reg[0] = *(program_count + 1);

            if (reg[*(program_count + 1) & 0x0F] == 0)
                flag = flag | 0b00001000;
            else
                flag = flag & 0b11110111;

            program_count = program_count + 2;
        }
        else if (*program_count == 0x05) //Rx postumis i kaire per 1 bita
        {
            reg[*(program_count + 1) & 0x0F] = reg[*(program_count + 1) & 0x0F] << 1;
            if (reg[*(program_count + 1) & 0x0F] == 0)
                flag = flag | 0b00001000;
            else
                flag = flag & 0b11110111;
            program_count = program_count + 2;
        }
        else if (*program_count == 0x06) //Rx postumis i desne per 1 bita
        {
            reg[*(program_count + 1) & 0x0F] = reg[*(program_count + 1) & 0x0F] >> 1;
            if (reg[*(program_count + 1) & 0x0F] == 0)
                flag = flag | 0b00001000;
            else
                flag = flag & 0b11110111;
            program_count = program_count + 2;
        }
        else if (*program_count == 0x07) // program_count + konstanta
        {
            program_count = program_count + (*(program_count + 1));
            flag = flag & 0b11110111;
        }
        else if (*program_count == 0x08) // Jei zeroFlag == 1, tai program_count + konstanta
        {
            if ((flag & 0b00001000) >> 3 == 1)
                program_count = program_count + (*(program_count + 1));
            else
                program_count = program_count + 2;
        }
        else if (*program_count == 0x09) //Jei zeroFlag == 0, tai program_count + konstanta
        {
            if ((flag & 0b00001000) >> 3 == 0)
                program_count = program_count + (*(program_count + 1));
            else
                program_count = program_count + 2;
        }
        else if (*program_count == 0x0A) //Jei eofFlag == 1, tai program_count + konstanta
        {
            if ((flag & 0b00010000) >> 4 == 1)
                program_count = program_count + (*(program_count + 1));
            else
                program_count = program_count + 2;
        }
        else if (*program_count == 0x0B) //VM baigia darba
        {
            break;
        }
        else if (*program_count == 0x0C) //Rx = Rx + Ry
        {
            reg[*(program_count + 1) & 0x0F] = reg[*(program_count + 1) & 0x0F] + reg[*(program_count + 1) >> 4];
            if (reg[*(program_count + 1) & 0x0F] == 0)
                flag = flag | 0b00001000;
            else
                flag = flag & 0b11110111;
            program_count = program_count + 2;
        }
        else if (*program_count == 0x0D) //Rx = Rx 2 Ry
        {
            reg[*(program_count + 1) & 0x0F] = reg[*(program_count + 1) & 0x0F] - reg[*(program_count + 1) >> 4];
            if (reg[*(program_count + 1) & 0x0F] == 0)
                flag = flag | 0b00001000;
            else
                flag = flag & 0b11110111;
            program_count = program_count + 2;
        }
        else if (*program_count == 0x0E) //Rx = Rx xor Ry
        {
            reg[*(program_count + 1) & 0x0F] = reg[*(program_count + 1) & 0x0F] ^ reg[*(program_count + 1) >> 4];
            if (reg[*(program_count + 1) & 0x0F] == 0)
                flag = flag | 0b00001000;
            else
                flag = flag & 0b11110111;
            program_count = program_count + 2;
        }
        else if (*program_count == 0x0F) //Rx = Rx or Ry
        {
            reg[*(program_count + 1) & 0x0F] = reg[*(program_count + 1) & 0x0F] | reg[*(program_count + 1) >> 4];
            if (reg[*(program_count + 1) & 0x0F] == 0)
                flag = flag | 0b00001000;
            else
                flag = flag & 0b11110111;
            program_count = program_count + 2;
        }
        else if (*program_count == 0x10) // Skaito viena baita is failo ir priskiria Rx, eofFlag jei pasiekta failo pabaiga
        {
            if (!fd.get(reg[*(program_count + 1) & 0x0F])) {
                flag = flag | 0b00010000;
            }
            program_count = program_count + 2;
        }
        else if (*program_count == 0x11) // Cout << Rx
        {
            cout << reg[*(program_count + 1) & 0x0F];

            program_count = program_count + 2;
        }
    }
    fd.close();
}