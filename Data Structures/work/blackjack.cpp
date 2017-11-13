#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "deck.h"
#include "card.h"
#include "player.h"
#include "rand.h"
#include "player.h"

using namespace std;

int main(int argc, char* argv[])
{
    int cut, bankroll, handnum, bet;
    string selectMode;
    HandValue tempValue;
    Hand player, dealer;
    Deck a;
    Card nextCard, DealerUpCard, DealerHoleCard;
    cout << "Shuffling the deck\n";
    
    for(int i = 0; i < 7; i++)
    {
    cut = get_cut();
    cout << "cut at " << cut ;
    a.shuffle(cut); 
    }   
    bankroll = atoi(argv[1]);
    handnum = atoi(argv[2]);
    selectMode = argv[3];
        Player *Realplayer;

        if(selectMode == "simple")
        {
            Realplayer = get_Simple();
        }
        if(selectMode == "counting")
        {
            Realplayer = get_Counting();
        }
        
        Realplayer->shuffled();
        for(int i = 1; i < handnum + 1; i++)
        {
            cout << "Hand " << i << " bankroll " << bankroll << endl;
            if(a.cardsLeft() < 20)
            {
                a.shuffle(get_cut());
                Realplayer->shuffled();
            }
            bet = Realplayer->bet(bankroll , 5);
            cout << "Player bets " << bet << endl;

            nextCard = a.deal();
            cout << "Player dealt " << SpotNames[nextCard.spot] << " of "  << SuitNames[nextCard.suit] << endl;
            player.addCard(nextCard);
            Realplayer->expose(nextCard);

            nextCard = a.deal();
            DealerUpCard = nextCard;
            cout << "Dealer dealt " << SpotNames[nextCard.spot] << " of "  << SuitNames[nextCard.suit] << endl;
            dealer.addCard(nextCard);
            Realplayer->expose(nextCard);
     
            nextCard = a.deal();
            cout << "Player dealt " << SpotNames[nextCard.spot] << " of "  << SuitNames[nextCard.suit] << endl;
            player.addCard(nextCard);
            Realplayer->expose(nextCard);

            nextCard = a.deal();
            DealerHoleCard = nextCard;
            dealer.addCard(nextCard);

            tempValue = player.handValue();
            if(tempValue.count == 21)
            {
                cout << "Player dealt natural 21" << endl;
                bankroll = bankroll + bet * 3 / 2;
                player.discardAll();
                dealer.discardAll();
                continue;
            }
            while(Realplayer->draw(DealerUpCard, player))
            {
                nextCard = a.deal();
                cout << "Player dealt " << SpotNames[nextCard.spot] << " of "  << SuitNames[nextCard.suit] << endl;
                player.addCard(nextCard);
            }
            cout << "Player's total is " << player.handValue().count << endl;
            if(player.handValue().count > 21)
            {
                cout << "Player busts\n";
                bankroll = bankroll - bet;
                player.discardAll();
                dealer.discardAll();
                continue;
            }
            cout << "Dealer's hole card is " <<  SpotNames[DealerHoleCard.spot] << " of "  << SuitNames[DealerHoleCard.suit] << endl;
            //Realplayer->expose(DealerHoleCard);
            while(dealer.handValue().count < 17)
            {
                nextCard = a.deal();
                cout << "Dealer dealt " << SpotNames[nextCard.spot] << " of "  << SuitNames[nextCard.suit] << endl;
                dealer.addCard(nextCard);
            }   
            cout << "Dealer's total is " <<  dealer.handValue().count << endl;        
            if(dealer.handValue().count > 21)
            {
                cout << "Dealer busts\n";
                bankroll = bankroll + bet;
                player.discardAll();
                dealer.discardAll();
                continue;
            }
            if(player.handValue().count > dealer.handValue().count)
            {
                cout << "Player wins\n";
                bankroll = bankroll + bet;
                player.discardAll();
                dealer.discardAll();
                continue;
            }
            if(player.handValue().count < dealer.handValue().count)
            {
                cout << "Dealer wins\n";
                bankroll = bankroll - bet;
                player.discardAll();
                dealer.discardAll();
                continue;
            }
            if(player.handValue().count == dealer.handValue().count)
            {
                cout << "Push\n";
                player.discardAll();
                dealer.discardAll();
                continue;
            }
            
        }
    
    cout << "Player has " << bankroll << " after " << handnum << " hands\n";
}






















