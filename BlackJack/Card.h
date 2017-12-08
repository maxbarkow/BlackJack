//These are the necessary libraries for the Card structure
#pragma once
#include<iostream>
#include<vector>
#include <string>
using namespace std;

struct Card {
    
    //Here we declare the variables for Card
    int value;
    char suit;
    
    //This constructor will initialize the variables with the passed values
    Card(int cNum, char theSuit) : value(cNum), suit(theSuit) { }
    Card() {
        
    }
    
    //This method is used to display the card's value and suit
    string displayCard() {
        string temp = "";
        switch (value) {
            case 10:
                temp += "10";
                break;
            case 11:
                temp += 'J';
                break;
            case 12:
                temp += 'Q';
                break;
            case 13:
                temp += 'K';
                break;
            case 1:
                temp += 'A';
                break;
            default:
                temp += ('0' + value);
                break;
        }
        
        temp += suit;
        return temp;
    }
    
};
