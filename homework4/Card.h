#pragma once
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_PIPS = 13;
const int NUM_SUITS = 4;
const string suitNames[NUM_SUITS] = { "Clubs", "Diamonds", "Hearts", "Spades" };
const string pipsNames[MAX_PIPS + 1] = { "", "Ace", "2", "3",
"4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };

class Card
{

private:
    int pips;
    int suitNum;

public:
    Card(void);
    Card(int pNum,
	   int sNum);

    int getPips() const { return pips; }
    int getSuitNum()const { return suitNum; }
    const string *getPipsName() const;
    const string *getSuitName() const;

    bool setPips(int pNum);
    bool setSuit(int sNum);

    bool operator < (const Card& card);
    bool operator > (const Card& card);
    bool operator == (const Card& card);

    friend ostream &operator << (ostream &strm, const Card &card);
};

Card::Card(void)
{
    pips = 1;
    suitNum = 0;
}


Card::Card(int pNum,
    int sNum)
{
    pips = 1;
    suitNum = 0;
    setPips(pNum);
    setSuit(sNum);
} // end constructor #2

const string *Card::getPipsName() const
{
    return &(pipsNames[pips]);
}

const string *Card::getSuitName() const
{
    return &(suitNames[suitNum]);
}

bool Card::setPips(int pNum)
{
    if (pNum >= 1 && pNum <= MAX_PIPS){
	   pips = pNum;
	   return true;
    }
    return false;
}

bool Card::setSuit(int sNum)
{
    if (sNum >= 0 && sNum < NUM_SUITS){
	   suitNum = sNum;
	   return true;
    }// end if
    return false;
}


bool Card::operator < (const Card& card)
{
    int diff = this->pips - card.pips;
    if (diff != 0)
	   return (diff < 0);
    // pips are the same, so compare suits
    diff = this->suitNum - card.suitNum;
    return (diff < 0);
}

bool Card::operator >(const Card& card)
{
    int diff = this->pips - card.pips;
    if (diff != 0)
	   return (diff > 0);
    // pips are the same, so compare suits
    diff = this->suitNum - card.suitNum;
    return (diff > 0);
}

bool Card::operator == (const Card& card)
{
    return this->pips == card.pips && this->suitNum == card.suitNum;
}


ostream &operator << (ostream &strm, const Card &card)
{
    strm << *(card.getPipsName()) << " of " << *(card.getSuitName()) << endl;
    return strm;
}
