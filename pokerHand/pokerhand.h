#ifndef POKERHAND_H
#define POKERHAND_H

#include "../Card/card.h"
#include <vector>
#include <iostream>

enum class HandType {
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
};

class PokerHand {
public:
    explicit PokerHand(const std::vector<Card>& hand);

    [[nodiscard]] HandType getHandType() const;
    [[nodiscard]] Rank getHighestRank() const;
    [[nodiscard]] Rank getRankAtPosition(int position) const;
    static int compareHands(const PokerHand& hand1, const PokerHand& hand2);

    [[nodiscard]] bool isHighCard() const;
    [[nodiscard]] bool isPair() const;
    [[nodiscard]] bool isTwoPair() const;
    [[nodiscard]] bool isThreeOfAKind() const;
    [[nodiscard]] bool isStraight() const;
    [[nodiscard]] bool isFlush() const;
    [[nodiscard]] bool isFullHouse() const;
    [[nodiscard]] bool isFourOfAKind() const;
    [[nodiscard]] bool isStraightFlush() const;
    std::vector<Card> getBestHand(const PokerHand& hand1, const PokerHand& hand2);

    void printHandType() const;

private:
    std::vector<Card> hand;
    bool isBetterHand(const std::vector<Card>& hand1, const std::vector<Card>& hand2) const;
    Card getCardAtPosition(int position) const;
};

#endif  // POKERHAND_H
