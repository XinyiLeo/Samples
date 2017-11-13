#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "hand.h"


Hand::Hand()
{
    discardAll();
};

void Hand::discardAll()
{
    curValue.count = 0;
    curValue.soft = false;
}

void Hand::addCard(Card c)
{
     switch (c.spot)
            {  
                case ACE:  
                    curValue.soft = true;
                    curValue.count = curValue.count + 11;
                    break;
                case TWO:  
                    curValue.count = curValue.count + 2;
                    break;    
                case THREE:  
                    curValue.count = curValue.count + 3;
                    break;
                case FOUR:  
                    curValue.count = curValue.count + 4;
                    break;
                case FIVE:  
                    curValue.count = curValue.count + 5;
                    break;
                case SIX:  
                    curValue.count = curValue.count + 6;
                    break;    
                case SEVEN:  
                    curValue.count = curValue.count + 7;
                    break;
                case EIGHT:  
                    curValue.count = curValue.count + 8;
                    break;
                case NINE:  
                    curValue.count = curValue.count + 9;
                    break;
                case TEN:  
                    curValue.count = curValue.count + 10;
                    break;    
                case JACK:  
                    curValue.count = curValue.count + 10;
                    break;
                case QUEEN:  
                    curValue.count = curValue.count + 10;
                    break;
                case KING:  
                    curValue.count = curValue.count + 10;
                    break;
            } 
         if(curValue.soft == true && curValue.count > 21)
         {
            curValue.soft = false;
            curValue.count = curValue.count - 10;
         }
}


HandValue Hand::handValue() const
{
    HandValue temp;
    temp.count = curValue.count;
    temp.soft = curValue.soft;
    return temp;
}

