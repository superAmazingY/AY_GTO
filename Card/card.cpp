#include "card.h"

Card::Card(Suit s, Rank r) : suit(s), rank(r) {}

Rank Card::getRank() const {
    return rank;
}

Suit Card::getSuit() const {
    return suit;
}

std::string Card::getSuitString() const {
    switch (suit) {
        case Suit::CLUBS:
            return "Clubs";
        case Suit::DIAMONDS:
            return "Diamonds";
        case Suit::HEARTS:
            return "Hearts";
        case Suit::SPADES:
            return "Spades";
        default:
            return "Unknown";
    }
}

std::string Card::getRankString() const {
    switch (rank) {
        case Rank::ACE:
            return "Ace";
        case Rank::TWO:
            return "2";
        case Rank::THREE:
            return "3";
        case Rank::FOUR:
            return "4";
        case Rank::FIVE:
            return "5";
        case Rank::SIX:
            return "6";
        case Rank::SEVEN:
            return "7";
        case Rank::EIGHT:
            return "8";
        case Rank::NINE:
            return "9";
        case Rank::TEN:
            return "10";
        case Rank::JACK:
            return "Jack";
        case Rank::QUEEN:
            return "Queen";
        case Rank::KING:
            return "King";
        default:
            return "Unknown";
    }
}


