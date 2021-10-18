// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len):BitLen(len)
{
	if (len < 0) throw "Negative len";
	MemLen = len / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) : BitLen(bf.BitLen), MemLen(bf.MemLen) // конструктор копирования
{
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (1 << n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= BitLen || n < 0) throw "Out of range size";
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= BitLen || n < 0) throw "Out of range size";
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= BitLen || n < 0) throw "Out of range size";
	if (pMem[GetMemIndex(n)] & GetMemMask(n)) return 1;
	else return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{ 
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return false;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i]) return false;
	return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return true;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i]) return true;
	return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField res(0);
	if (BitLen > bf.BitLen)
	{
		res = *this;
		for (int i = 0; i < bf.MemLen; i++)
			res.pMem[i] |= bf.pMem[i];
	}
	else
	{
		res = bf;
		for (int i = 0; i < MemLen; i++)
			res.pMem[i] |= pMem[i];
	}

	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField res(0);
	if (BitLen > bf.BitLen)
	{
		res = *this;
		for (int i = 0; i < bf.MemLen; i++)
			res.pMem[i] &= bf.pMem[i];
	}
	else
	{
		res = bf;
		for (int i = 0; i < MemLen; i++)
			res.pMem[i] &= pMem[i];
	}

	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if (!GetBit(i)) res.SetBit(i);
	}

	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		bool value;
		istr >> value;
		bf.SetBit(value);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}
