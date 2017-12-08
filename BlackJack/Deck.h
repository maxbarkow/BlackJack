//These are the libraries necessary for the Deck class
#pragma once
#include<iostream>
#include<vector>
#include <string>
#include "Card.h"
using namespace std;


class Deck {
private:
    //Declaring an array of 52 cards representing the Deck
    Card cards[52];
public:
    
    //Deck constructor which initializes all of the elements in the cards array to their respective values and suits
    Deck() {
        
        int k = 0;
        
        /*This loops assings one of the four suits to each card.
         The following for loop assigns a number from 1 to 13, with 1 being "A",
         and 11-13 being face cards.
         */
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                if (i == 0) {
                    cards[k] = Card(j + 1, 'D');
                    k++;
                }
                else if (i == 1) {
                    cards[k] = Card(j + 1, 'S');
                    k++;
                }
                else if (i == 2) {
                    cards[k] = Card(j + 1, 'C');
                    k++;
                    
                }
                else if (i == 3) {
                    cards[k] = Card(j + 1, 'H');
                    k++;
                }
            }
        }
    }
    
    //Method returning a Card from the Deck
    Card getCard(int randCard) {
        Card temp = cards[randCard];
        return temp;
    }
    
};
