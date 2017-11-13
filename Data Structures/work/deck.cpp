#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "deck.h"
using namespace std;

Deck::Deck() {
    int it = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {    
            switch (i)
            {  
                case 0:  
                    deck[it].suit = SPADES;
                    break;
                case 1:  
                    deck[it].suit = HEARTS;
                    break;    
                case 2:  
                    deck[it].suit = CLUBS;
                    break;
                case 3:  
                    deck[it].suit = DIAMONDS;
                    break;
            } 
            switch (j)
            {  
                case 0:  
                    deck[it].spot = TWO;
                    break;
                case 1:  
                    deck[it].spot = THREE;
                    break;    
                case 2:  
                    deck[it].spot = FOUR;
                    break;
                case 3:  
                    deck[it].spot = FIVE;
                    break;
                case 4:  
                    deck[it].spot = SIX;
                    break;
                case 5:  
                    deck[it].spot = SEVEN;
                    break;    
                case 6:  
                    deck[it].spot = EIGHT;
                    break;
                case 7:  
                    deck[it].spot = NINE;
                    break;
                case 8:  
                    deck[it].spot = TEN;
                    break;
                case 9:  
                    deck[it].spot = JACK;
                    break;    
                case 10:  
                    deck[it].spot = QUEEN;
                    break;
                case 11:  
                    deck[it].spot = KING;
                    break;
                case 12:  
                    deck[it].spot = ACE;
                    break;    
            } 
            it++;
        }    
    } 
    next = -1;
}

void Deck::reset()
{
   Deck b;
   for(int i = 0; i < DeckSize; i++)
   {
   deck[i] = b.deck[i];
   }
   next = b.next; 
}

void Deck::shuffle(int n)
{
    Card left[n];
    Card right[52 - n];
    for(int i = 0; i < n; i++ )
    {
        left[i] = deck[i];
        //cout << setw(6) << SpotNames[left[i].spot] << " of " << setw(8) << SuitNames[left[i].suit] << endl;
    }
    cout << endl;
    for(int i = 0; i < 52 - n; i++ )
    {
        right[i] = deck[n + i];
        //cout << setw(6) << SpotNames[right[i].spot] << " of " << setw(8) << SuitNames[right[i].suit] << endl;
    }
    if (n > 0 && n < 26)
    {
        for(int i = 0; i < n; i++)
        {
            deck[2 * i] = right[i];
            deck[2 * i + 1] = left[i];
        }        
        for(int i = n; i < 52 - n ; i++)
        {
            deck[n + i] = right[i];
        }
    }
    else if(n == 26)
    {
        for(int i = 0; i < 26; i++)
        {
            deck[2 * i] = right[i];
            deck[2 * i + 1] = left[i];
        }      
    }
    else if(n > 26 && n < 52)
    {
        for(int i = 0; i < 52 - n; i++)
        {
            deck[2 * i] = right[i];
            deck[2 * i + 1] = left[i];
        }        
        for(int i = 52 - n; i < n ; i++)
        {
            deck[52- n + i] = left[i];
        }
    }
    next = -1;
}

Card Deck::deal()
{
    next++;
    if(next >= 52)
        throw deck[next];
    else
    return deck[next];
}

int Deck::cardsLeft()
{
    return 51 - next;
}

/*
void Deck::natural()
{
    deck[6].spot = ACE;
    deck[8].spot = KING;
}
*/


