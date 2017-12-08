//These are the necessary libraries for the Dealer class
#include<iostream>
#include<vector>
#include <string>
#include "Deck.h"
#include <cstdlib>
using namespace std;

class Dealer {
private:
    //Necessary variables for the Dealer class
    bool isNull[6][52];
    Deck deckList[7];
    vector <Card> hand;
    
public:
    /*Dealer constructor that will create 7 decks, 1 used as a default deck and then 6 more decks
     are the ones used to play.
     */
    Dealer() {
        for (int i = 0; i < 7; i++) {
            deckList[i] = Deck();
        }
        
        /*This for loop initializes all the elementes in the multidimensional array "isNull"
         which's purpose is going to be to record which card has been drawn and which one hasn't
         */
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 52; j++) {
                isNull[6][52] = false;
            }
        }
    }
    
    //This function is going to return a Card when the player wants to hit
    Card playerHit() {
        
        //Randomization to ensure that the player is going to receive a totally random card from the decks
        int randCard = rand() % 52;
        int randDeck = rand() % 6 + 1;
        
        //This checks if the card that we are taking out is avaliable, if it is not then find a diffented card that it is.
        while (isNull[randDeck - 1][randCard]) {
            randCard++;
            randDeck++;
            if (randCard == 52) {
                randCard = 0;
            }
            if (randDeck == 7) {
                randDeck = 1;
            }
        }
        isNull[randDeck - 1][randCard] = true;
        Card randomCard = deckList[randDeck].getCard(randCard);
        return randomCard;
    }
    
    //This method adds a card to the dealer's "hand"
    void hit(Card tempCard) {
        hand.push_back(tempCard);
    }
    
    //This method displays the values and suits of all the cards in the decks
    void displayDeck() {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 52; j++) {
                cout << deckList[i].getCard(j).displayCard() << " ";
            }
        }
    }
    
    //This function will return the sum of the dealer's "hand"
    int cardSum() {
        int temp;
        int sum = 0;
        //This for loops performs the computation for the sum
        for (int i = 0; i < hand.size(); i++) {
            temp = hand[i].value;
            //If the value is between 11 and 13 add 10 to the sum, because that is the value of a face card.
            if (temp == 11 || temp == 12 || temp == 13) {
                sum += 10;
            }
            else {
                sum += temp;
            }
        }
        return sum;
    }
    
    //This funtion will initialize all the elements in the Deck array "deckList" with Deck objects
    void setDecks() {
        for (int i = 0; i < 7; i++) {
            deckList[i] = Deck();
        }
    }
    
    //This function is going to clear the dealer's hand
    void clearHand()
    {
        hand.clear();
    }
};
