//These are the libraries necessary for the Player class
#include "Card.h"
#include "Dealer.h"
#include "Deck.h"
#include<iostream>
#include<vector>
#include <string>
using namespace std;

class Player {
private:
    //These are the declarations for the variables used in the class
    bool bust = false;
    string name;
    int money;
    vector <Card> hand;
    
public:
    //Player constructor that will initialize the variables "name" and "money" with the values passed.
    Player(string playerName, int playerMoney) {
        name = playerName;
        money = playerMoney;
    }
    Player() {
        
    }
    /*This function deals with the betting process and checks if the entered amount is a valid amount.
     */
    int betAmount(int money) {
        int bet;
        cout << "Please enter how much you want to bet:  $";
        cin >> bet;
        while (bet > money) {
            cout << "You cannot bet more than you have." << endl;
            cout << "Please enter how much you want to bet:  $";
            cin >> bet;
        }
        return bet;
    }
    
    //Function that will add a Card to the player's vector "hand" if they chose to hit
    void hit(Card tempCard) {
        hand.push_back(tempCard);
    }
    
    //Function returning the total card sum of the player's hand
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
    
    //This function adds a card to the player's hand
    void addCard(Card cardToAdd) {
        hand.push_back(cardToAdd);
        return;
    }
    
    //This method will return the amount of money the player currently has
    int getMoney() {
        return money;
    }
    
    //This method will return the player's name
    string getName() {
        return name;
    }
    
    //This function will display the hand of the player
    void showHand() {
        for (int i = 0; i < hand.size(); i++) {
            cout << hand[i].displayCard() << " ";
        }
        cout << endl;
    }
    
    //This function is used to clear the hand of the player.
    void clearHand()
    {
        hand.clear();
    }
    
    //This function will confirm that a player busted
    void setBust() {
        bust = true;
    }
    
    //This function returns the result of whether the player has busted or not
    bool getBust() {
        return bust;
    }
    
    //This function will return the amount of money the player has after the result of the bet.
    int betResult(int betAmount) {
        money += betAmount;
        return money;
    }
    
};
