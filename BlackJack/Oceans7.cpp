// @authors Ben Lassley, Leandro Castro, Rachel Nutter, Christian Toro, Cooper Adams, Max Barkow, Anthony Voong
//
//Includes all the libraries that we used for the project.
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Player.h"
#include <ctime>
using namespace std;

int main() {
    /*Here, we set up constant values for the starting amount of money each player receives
     as well as the amount of money needed to win the whole game and the amount to
     lose the game.
     */
    const int WIN_AMOUNT = 10000;
    const int START_AMOUNT = 1000;
    const int LOSE_AMOUNT = 0;
    
    //This serves to randomize our values.
    srand(time(NULL));
    
    //This is where we initialize our variables and objects.
    
    int temp;
    int betAmount = 0;
    int hitOrStay = 0;
    int cardSum = 0;
    int playerNum = 1;
    bool dealerBlackjack = false;
    bool correctPlayers = false;
    Card tempCard;
    Dealer thisDealer;
    string playerName = "";
    vector <Player> playerList;
    vector <int> winners;
    vector <int> push;
    
    //This is a for loop that creates our title screen.
    for (int i = 0; i < 7; i++) {
        if (i == 3) {
            cout << "XXXXXXXXXXXXXXXXXX WELCOME TO OCEAN'S BLACKJACK XXXXXXXXXXXXXXXXXX\n";
        }
        else if (i == 2 || i == 4) {
            cout << "XXXXXXXXXXXXXXXXXX                              XXXXXXXXXXXXXXXXXX\n";
        }
        else cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";
        
    }
    
    
    cout << "\nHow many players are there? (Max of 4)\n";
    do {
        cin >> playerNum;
        //Checks if input is int. If not or the integer is greater than the max int size //possible, then prompts user to re-input integer instead of entering an endless
        //loop or crashing.
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Incorrect input. Please choose a player number between 1 and 4.\n";
        }
        
        /*If the user does successfully input an integer but is outside our range of allowed players,
         tell them that that is not allowed and have them input another integer.
         */
        else if (playerNum > 4 || playerNum < 1) {
            cout << "Incorrect amount of players. Please choose a player number between 1 and 4.\n";
        }
        else {
            /*In this for loop, we go through and allow the user to name each player that they created
             by their input, assign each player the starting amount of money, and put them into a vector
             array.
             */
            for (int i = 1; i <= playerNum; i++) {
                cout << "Enter player " << i << "'s name: " << endl;
                cin >> playerName;
                cout << endl;
                
                playerList.push_back(Player(playerName, START_AMOUNT));
            }
            correctPlayers = true;
        }
    } while (!correctPlayers);
    
    //This loop is where the game takes place.
    while (true) {
        bool dealerStay = false;
        bool dealerBust = false;
        
        //In this loop, we are giving each player two cards to start.
        for (int i = 0; i < playerNum; i++) {
            for (int j = 0; j < 2; j++) {
                tempCard = thisDealer.playerHit();
                playerList[i].hit(tempCard);
            }
            
        }
        
        //In this loop, we are giving the dealer his/her pair of cards.
        for (int i = 0; i < 2; i++) {
            
            tempCard = thisDealer.playerHit();
            thisDealer.hit(tempCard);
        }
        
        /*For this loop, we are creating the algorithm for the dealer's actions.
         If the dealer has a hand of less than 17, he/she has to take a
         hit. Otherwise, the dealer stays.
         */
        bool dealerBool = true;
        do {
            if (thisDealer.cardSum() < 17) {
                tempCard = thisDealer.playerHit();
                thisDealer.hit(tempCard);
            }
            else if (thisDealer.cardSum() >= 17 && thisDealer.cardSum() <= 21) {
                dealerBool = false;
            }
            
            else if (thisDealer.cardSum() == 21) {
                dealerBlackjack = true;
                thisDealer.clearHand();
            }
            
            else if (thisDealer.cardSum() > 21) {
                dealerBool = false;
            }
            
        } while (dealerBool);
        
        /* In this for loop, we are checking if all the players have no money left
         and if that is the case, we exit the program because there is no one
         left to play the game.
         */
        for (int i = 0; i < playerNum; i++) {
            bool stay = false;
            int j = 0;
            
            for (int k = 0; k < playerNum; k++)
            {
                
                if (playerList[k].getMoney() == LOSE_AMOUNT) {
                    j++;
                    if (j == playerNum)
                    {
                        cout << "No remaining players, game over!\n\n" << endl;
                        exit(0);
                    }
                }
            }
            
            /*This is the other condition for exiting the program. It is also the only
             way to win the game. Once a player reaches $10,000 dollars, they automatically
             win the game. This way, a player can not play endlessly.
             */
            for (int i = 0; i < playerNum; i++)
            {
                
                if (playerList[i].getMoney() >= WIN_AMOUNT)
                    
                {
                    cout << playerList[i].getName() << ", congratulations, you've won!!!\n\n" << endl;
                    exit(0);
                }
                
                
            }
            
            /*In this conditional statement, we are checking to see if a player has reached bankrupcy
             or not. If so, the game will remind them that that player can no longer play the game and
             will not let them perform any actions.
             */
            if (playerList[i].getMoney() == 0) {
                cout << "\n" << playerList[i].getName() << ", you have been exited from the game\n" << endl;
                playerList[i].clearHand();
                continue;
            }
            
            /*This loop takes in all the bets for each player as stores it so it can later be
             added, subtracted, or pushed back into their wallet.
             */
            cout << playerList[i].getName() << ", you have $" << playerList[i].getMoney() << endl;
            do {
                cout << "What amount would you like to bet? Please enter a number between 0 and your amount of money" << endl;
                cin >> betAmount;
                cout << "\n";
            } while (!(betAmount > 0 && betAmount <= playerList[i].getMoney()));
            
            cout << "Bet Amount: " << betAmount << endl;
            
            /*This is where we look at each player's hand and calculate the total sum
             for their cards. Then they have the option to hit for another card
             or stay if they are satisfied with the total of their cards.
             */
            do {
                cout << playerList[i].getName() << ", your hand is: " << endl;
                playerList[i].showHand();
                cout << "Your hand adds up to: " << playerList[i].cardSum() << endl;
                
                cout << "\nType 1 to hit, 2 to stay" << endl;
                cin >> hitOrStay;
                if (playerList[i].cardSum() < 21 && hitOrStay == 1) {
                    tempCard = thisDealer.playerHit();
                    playerList[i].hit(tempCard);
                    cardSum = playerList[i].cardSum();
                    stay = true;
                }
                else if (hitOrStay == 2) {
                    cardSum = playerList[i].cardSum();
                    stay = false;
                }
                
                //If the player ends up busting, we make sure they cannot hit anymore.
                if (cardSum > 21) {
                    stay = false;
                }
                
                
            } while (stay);
            
            /*This conditional statement checks to see if the dealer has busted. If so,
             we set the bool variable to true and clear the dealer's hand.
             */
            bool dealerBust = false;
            if (thisDealer.cardSum()> 21)
            {
                dealerBust = true;
                if (i == (playerNum - 1)) {
                    thisDealer.clearHand();
                }
                
            }
            temp = thisDealer.cardSum();
            /*If a player's hand is less than the dealer's hand and as long as the dealer has
             not busted, the player will lose the amount that they betted and the player's
             and dealer's hand will be cleared for another round.
             */
            if (cardSum < thisDealer.cardSum() && thisDealer.cardSum() <= 21) {
                
                playerList[i].betResult(-betAmount);
                cout << "Your Total: " << playerList[i].cardSum() << "\n" << endl;
                
                playerList[i].clearHand();
                if (i == playerNum - 1) {
                    thisDealer.clearHand();
                }
            }
            
            /*Since we are hitting the players before the dealer, if the player has a hand that
             has busted, they will lose their money even if the dealer ends up busting. Then the
             player's and dealer's hand will be cleared for another round.
             */
            else if (cardSum > 21)
            {
                playerList[i].betResult(-betAmount);
                cout << playerList[i].getName() << ", unfortunately you busted.  Your cards added up to " << playerList[i].cardSum() << endl;
                cout << playerList[i].getName() << ", you now have $" << playerList[i].getMoney() << "\n" << endl;
                playerList[i].clearHand();
                if (i == playerNum - 1) {
                    thisDealer.clearHand();
                }
            }
            
            /*Here, if the player's card total is under 21 and if the their total is greater
             than the dealer's total or if the dealer busts, then the player wins and they get
             their bet amount added to their wallet. The player's and dealer's hand will be cleared
             for another round.
             */
            else if (cardSum < 21 && (cardSum > thisDealer.cardSum() || dealerBust)) {
                playerList[i].betResult(betAmount);
                cout << "Your Total: " << playerList[i].cardSum() << "\n" << endl;
                playerList[i].clearHand();
                winners.push_back(i);
                if (i == playerNum - 1) {
                    thisDealer.clearHand();
                }
            }
            
            /*This is where we are checking to see if a player has a hand value equal to the
             dealer's. If so, they do not lose or gain any money, which is known as a push.
             Then, their hand and the dealer's hand is cleared for another round. 
             */
            else if (cardSum == thisDealer.cardSum()) {
                cout << "Your Total: " << playerList[i].cardSum() << "\n" << endl;
                playerList[i].clearHand();
                push.push_back(i);
                if (i == playerNum - 1) {
                    thisDealer.clearHand();
                }
            }
            
            /*This conditional statement checks if the player has reached blackjack and did
             not match the dealer in hand value. This makes it so the player gets double their
             bet amount back. Afterwards, their hand and the dealer's hand is cleared for another
             round.
             */
            else if (cardSum == 21) {
                playerList[i].betResult(betAmount*2);
                cout << "Your Total: " << playerList[i].cardSum() << "\n" << endl;
                cout << "Congratulations on getting Blackjack!!!\n" << endl;
                playerList[i].clearHand();
                winners.push_back(i);
                if (i == playerNum - 1) {
                    thisDealer.clearHand();
                }
                
            }
            
            /*Anything else that is not caught will just reset everyone's hands.
             */
            else {
                playerList[i].clearHand();
                if (i == playerNum - 1) {
                    thisDealer.clearHand();
                }
            }
            
        }
        
        //All the winners are are displayed in this loop after we have stored them in the previous conditional statements. 
        cout << "Winners:" << endl;
        for (int i = 0; i < winners.size(); i++){
            string temp = playerList[winners[i]].getName();
            cout << temp << " ";
        }
        //Empty the vector for the next round.
        winners.clear();
        cout << endl;
        
        //Every player that tied with the dealer are displayed in this loop after we stored them in the previous conditional statements.
        cout << "Tied with Dealer:" << endl;
        for (int i = 0; i < push.size(); i++) {
            string temp = playerList[push[i]].getName();
            cout << temp << " ";
        }
        
        //Empty the vector for the next round.
        push.clear();
        cout << endl;
        
        cout << "\n\nNEXT ROUND, GOOD LUCK. \n\n" << endl;
        
    }
    
    
    return 0;
    
};



