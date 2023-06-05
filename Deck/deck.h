#ifndef DECK_H
#define DECK_H

#include "../Card/card.h"
#include <vector>
#include <random>

class Deck {
public:
    Deck();
    void shuffle();
    Card dealCard();
    [[nodiscard]] int getNumCards() const;

private:
    std::vector<Card> cards;
    std::default_random_engine randomEngine;
};

#endif  // DECK_H
