#include "Card/card.h"
#include "Deck/deck.h"
#include "pokerHand/pokerhand.h"

int main() {
    Deck deck;
    deck.shuffle();
    std::cout << "Dealing cards..." << std::endl;

    std::vector<Card> hand1;
    std::vector<Card> hand2;

    for (int i = 0; i < 5; ++i) {
        Card card1 = deck.dealCard();
        hand1.push_back(card1);
        std::cout << "Dealt card 1: " << card1.getRankString() << " of " << card1.getSuitString() << std::endl;

        Card card2 = deck.dealCard();
        hand2.push_back(card2);
        std::cout << "Dealt card 2: " << card2.getRankString() << " of " << card2.getSuitString() << std::endl;
    }

    PokerHand pokerHand1(hand1);
    PokerHand pokerHand2(hand2);

    HandType handType1 = pokerHand1.getHandType();
    HandType handType2 = pokerHand2.getHandType();

    pokerHand1.printHandType();
    pokerHand2.printHandType();

    if (handType1 > handType2) {
        std::cout << "Hand 1 wins!" << std::endl;
    } else if (handType1 < handType2) {
        std::cout << "Hand 2 wins!" << std::endl;
    } else {
        int result = PokerHand::compareHands(pokerHand1, pokerHand2);

        if (result == 1) {
            std::cout << "Hand 1 wins!" << std::endl;
        } else if (result == -1) {
            std::cout << "Hand 2 wins!" << std::endl;
        } else {
            std::cout << "It's a tie!" << std::endl;
        }
    }
    return 0;
}



