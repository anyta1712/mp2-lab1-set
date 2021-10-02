// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -2;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0) throw  "Error.The wrong size of lenth (< 0) .";
    BitLen = len;
    if (BitLen % 32 == 0) { MemLen = BitLen / 32; }
    else { MemLen = BitLen / 32 + 1; }
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    if (BitLen < 0) throw "Error.The wrong size of lenth (< 0) .";
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }

}

TBitField::~TBitField()
{
    delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n/32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM res = 1;
    res = res << n % 32;
    return res;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen)) throw "The wrong position";
    int k;
    TELEM m;
    k = GetMemIndex(n);
    m = GetMemMask(n);
    pMem[k] |= m;

}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen)) throw "The wrong position";
    int k;
    TELEM m;
    k = GetMemIndex(n);
    m = ~GetMemMask(n);
    pMem[k] &= m;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n >= BitLen)) throw "The wrong position";
    int k;
    TELEM m;
    k = GetMemIndex(n);
    m = GetMemMask(n);
    return m & pMem[k];

 
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (bf.MemLen != MemLen) {
        delete[]pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
    }
    BitLen = bf.BitLen;
        for (int i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    return*this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
   int res = 1;
    if (BitLen != bf.BitLen)
        res = 0;
    else 
        for (int i = 0; i < MemLen-1; i++) {
            if (pMem[i] != bf.pMem[i])res = 0;
        }
    for (int i = 0; i < (MemLen - 1) * 32; i++) {
        if (GetBit(i) != bf.GetBit(i))res = 0;
    }

    return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this==bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int i, len = BitLen;
    if (bf.BitLen > len)
        len = bf.BitLen;
    TBitField temp(len);
    for (i = 0; i < MemLen; i++) {
        temp.pMem[i] = pMem[i];
    }
    for (i = 0; i < bf.MemLen; i++) {
        temp.pMem[i] |= bf.pMem[i];
    }
    return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int i, len = BitLen;
    if (bf.BitLen > len)
        len = bf.BitLen;
    TBitField temp(len);
    for (i = 0; i < MemLen; i++) {
        temp.pMem[i] = pMem[i];
    }
    for (i = 0; i < bf.MemLen; i++) {
        temp.pMem[i] &= bf.pMem[i];
    }
    return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
    int len = BitLen;
    TBitField temp(len);
    for (int i = 0; i < MemLen - 1; i++) {
        temp.pMem[i] = ~pMem[i];
       
    }
    for (int i = (MemLen - 1)*32; i < BitLen; i++) {
        if (!GetBit(i)) {
            temp.SetBit(i);
            (*this).pMem[i] = (*this).pMem[i] & temp.pMem[i];
        }
     
    }
    return temp;
}
// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char x;
    for (int i = 0; i < bf.BitLen; i++) {
        istr >> x;
        if (x == '0')bf.ClrBit(i);
        else if (x == '1')bf.SetBit(i);
        else break;
    }
    return istr;
}
ostream& operator<<(ostream& ostr, const TBitField& bf)//вывод
{
    for (int i = 0; i < bf.BitLen; i++) {
        if (bf.GetBit(i)) { ostr << 1; }
        else { ostr << 0; }
    }
    return ostr;
}
