#ifndef CARD_H
#define CARD_H

#include <string>

enum class Suit {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES,
    UNKNOWN
};

enum class Rank {
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    UNKNOWN
};

class Card {
public:
    Card(Suit s, Rank r);

    [[nodiscard]] std::string getSuitString() const;
    [[nodiscard]] std::string getRankString() const;

    [[nodiscard]] Suit getSuit() const;
    [[nodiscard]] Rank getRank() const;

private:
    Suit suit;
    Rank rank;
};

#endif  // CARD_H
