#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "player.h"
#include "hand.h"


class SimplePlayer : public Player {
public:
    SimplePlayer();
    int bet(unsigned int bankroll, unsigned int minimum);
    bool draw(Card dealer, const Hand &player);
    void expose(Card c);
    void shuffled();
};

class CountingPlayer : public SimplePlayer {
int count;
public:
    CountingPlayer();
    int bet(unsigned int bankroll, unsigned int minimum);
   // bool draw(Card dealer, const Hand &player);
    void expose(Card c);
    void shuffled();
};

SimplePlayer::SimplePlayer(){}

int SimplePlayer::bet(unsigned int bankroll, unsigned int minimum)
{
    return minimum;
}


bool SimplePlayer::draw(Card dealer, const Hand &player)
{
    HandValue temphand = player.handValue();
    if(temphand.soft == false)
    { 
        if(temphand.count <= 11)
        {
            return true;
        }
        else if (temphand.count == 12)
        {
            switch(dealer.spot)
            {
                case TWO:
                    return true;
                case THREE:
                    return true;
                case FOUR:
                    return false;
                case FIVE:
                    return false;
                case SIX:
                    return false;
                case SEVEN:
                    return true;
                case EIGHT:
                    return true;
                case NINE:
                    return true;
                case TEN:
                    return true;
                case JACK:
                    return true;
                case QUEEN:
                    return true;
                case KING:
                    return true;
                case ACE:
                    return true;
            }
        }
        else if (temphand.count >= 13 && temphand.count <= 16)
        {
            switch(dealer.spot)
            {
                case TWO:
                    return false;
                case THREE:
                    return false;
                case FOUR:
                    return false;
                case FIVE:
                    return false;
                case SIX:
                    return false;
                case SEVEN:
                    return true;
                case EIGHT:
                    return true;
                case NINE:
                    return true;
                case TEN:
                    return true;
                case JACK:
                    return true;
                case QUEEN:
                    return true;
                case KING:
                    return true;
                case ACE:
                    return true;
            }
        }
        else if (temphand.count >= 17)
        {
            return false;           
        }
    }
    if(temphand.soft == true)
    {
        if(temphand.count <= 17)
        {
            return true;
        }

        else if (temphand.count == 18)
        {
            switch(dealer.spot)
            {
                case TWO:
                    return false;
                case THREE:
                    return true;
                case FOUR:
                    return true;
                case FIVE:
                    return true;
                case SIX:
                    return true;
                case SEVEN:
                    return false;
                case EIGHT:
                    return false;
                case NINE:
                    return true;
                case TEN:
                    return true;
                case JACK:
                    return true;
                case QUEEN:
                    return true;
                case KING:
                    return true;
                case ACE:
                    return true;
            }
        }
        if(temphand.count >= 19)
        {
            return false;
        }
    }
    //Must add it, no use
    return true;
}

void SimplePlayer::expose(Card c){}
void SimplePlayer::shuffled(){}

CountingPlayer::CountingPlayer(){}
int CountingPlayer::bet(unsigned int bankroll, unsigned int minimum)
{
    if(count >= 2)
    {
        return 2*minimum;
    }
    else{return minimum;}
}



void CountingPlayer::expose(Card c)
{
     switch(c.spot)
            {
                case TWO:
                    count++;
                    break;
                case THREE:
                    count++;
                    break;
                case FOUR:
                    count++;
                    break;
                case FIVE:
                    count++;
                    break;
                case SIX:
                    count++;
                    break;
                case TEN:
                    count--;
                    break;
                case JACK:
                    count--;
                    break;
                case QUEEN:
                    count--;
                    break;
                case KING:
                    count--;
                    break;
                case ACE:
                    count--;
                    break;
                default:
                    count = count;
            }
}


void CountingPlayer::shuffled()
{
    count = 0 ;
}



static SimplePlayer Simple;
Player *get_Simple()
{
    return & Simple;
}

static CountingPlayer Counting;
Player *get_Counting()
{
    return & Counting;
}


