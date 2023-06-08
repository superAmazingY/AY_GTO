#include <algorithm>
#include "pokerhand.h"

PokerHand::PokerHand(const std::vector<Card> &hand) : hand(hand) {}

bool PokerHand::isHighCard() const {
    // 高牌：没有符合其他牌型的组合
    // 逻辑：排除其他牌型的情况即可
    return !isPair() && !isTwoPair() && !isThreeOfAKind() && !isStraight() && !isFlush() && !isFullHouse() &&
           !isFourOfAKind() && !isStraightFlush();
}

bool PokerHand::isPair() const {
    // 对子：有两张相同点数的牌
    // 逻辑：统计每个点数的牌的数量，如果有两张点数相同的牌，则为对子
    std::vector<Rank> ranks;
    for (const Card &card: hand) {
        ranks.push_back(card.getRank());
    }
    std::sort(ranks.begin(), ranks.end());

    for (size_t i = 0; i < ranks.size() - 1; ++i) {
        if (ranks[i] == ranks[i + 1]) {
            return true;
        }
    }
    return false;
}

bool PokerHand::isTwoPair() const {
    // 两对：有两个对子
    // 逻辑：统计每个点数的牌的数量，如果有两个点数各不相同的对子，则为两对
    std::vector<Rank> ranks;
    for (const Card &card: hand) {
        ranks.push_back(card.getRank());
    }
    std::sort(ranks.begin(), ranks.end());

    int pairCount = 0;
    for (size_t i = 0; i < ranks.size() - 1; ++i) {
        if (ranks[i] == ranks[i + 1]) {
            pairCount++;
            i++; // Skip the next card since it's part of the pair
        }
    }
    return pairCount == 2;
}

bool PokerHand::isThreeOfAKind() const {
    // 三条：有三张相同点数的牌
    // 逻辑：统计每个点数的牌的数量，如果有一张点数相同的牌出现三次，则为三条
    std::vector<Rank> ranks;
    for (const Card &card: hand) {
        ranks.push_back(card.getRank());
    }
    std::sort(ranks.begin(), ranks.end());

    for (size_t i = 0; i < ranks.size() - 2; ++i) {
        if (ranks[i] == ranks[i + 1] && ranks[i + 1] == ranks[i + 2]) {
            return true;
        }
    }
    return false;
}

bool PokerHand::isStraight() const {
    // 顺子：五张连续的牌（不考虑花色）
    // 逻辑：先将牌按点数排序，然后判断是否是连续的五张牌
    std::vector<Rank> ranks;
    for (const Card &card: hand) {
        ranks.push_back(card.getRank());
    }
    std::sort(ranks.begin(), ranks.end());

    for (size_t i = 0; i < ranks.size() - 1; ++i) {
        if (static_cast<int>(ranks[i]) + 1 != static_cast<int>(ranks[i + 1])) {
            return false;
        }
    }
    return true;
}

bool PokerHand::isFlush() const {
    // 同花：五张花色相同的牌
    // 逻辑：统计每个花色的牌的数量，如果有五张花色相同的牌，则为同花
    std::vector<Suit> suits;
/*    for (const Card &card: hand) {
        suits.push_back(card.getSuit());
    }
    for (const Card &card: hand) {
        Suit suit = card.getSuit();
        if (suit != Suit::CLUBS && suit != Suit::DIAMONDS && suit != Suit::HEARTS && suit != Suit::SPADES) {
            std::cerr << "Error: Invalid suit detected in hand!" << std::endl;
        }
    }
    if (suits.size() != 5) {
        std::cerr << "Error: Number of suits in hand is not 5!" << std::endl;
    }*/
    std::sort(suits.begin(), suits.end());
    for (int i = 0; i < suits.size() - 1; ++i) {
        if (suits[i] != suits[i + 1]) {
            return false;
        }
    }
    return true;
}

bool PokerHand::isFullHouse() const {
    // 葫芦：三条+对子
    // 逻辑：通过对牌进行计数，检查是否有三张和两张点数相同的牌
    std::vector<Rank> ranks;
    for (const Card &card: hand) {
        ranks.push_back(card.getRank());
    }
    std::sort(ranks.begin(), ranks.end());

    if (ranks[0] == ranks[1] && ranks[1] == ranks[2] && ranks[3] == ranks[4]) {
        return true;
    }

    if (ranks[0] == ranks[1] && ranks[2] == ranks[3] && ranks[3] == ranks[4]) {
        return true;
    }

    return false;
}

bool PokerHand::isFourOfAKind() const {
    // 四条：有四张相同点数的牌
    // 逻辑：统计每个点数的牌的数量，如果有一张点数相同的牌出现四次，则为四条
    std::vector<Rank> ranks;
    for (const Card &card: hand) {
        ranks.push_back(card.getRank());
    }
    std::sort(ranks.begin(), ranks.end());

    for (size_t i = 0; i < ranks.size() - 3; ++i) {
        if (ranks[i] == ranks[i + 1] && ranks[i + 1] == ranks[i + 2] && ranks[i + 2] == ranks[i + 3]) {
            return true;
        }
    }
    return false;
}

bool PokerHand::isStraightFlush() const {
    // 同花顺：既是同花又是顺子的牌
    // 逻辑：先判断是否是同花，再判断是否是顺子
    return isFlush() && isStraight();
}

void PokerHand::printHandType() const {
    if (isHighCard()) {
        std::cout << "The hand is a High Card!" << std::endl;
    }
    if (isPair()) {
        std::cout << "The hand is a Pair!" << std::endl;
    }
    if (isTwoPair()) {
        std::cout << "The hand is a Two Pair!" << std::endl;
    }
    if (isThreeOfAKind()) {
        std::cout << "The hand is a Three of a Kind!" << std::endl;
    }
    if (isStraight()) {
        std::cout << "The hand is a Straight!" << std::endl;
    }
    if (isFlush()) {
        std::cout << "The hand is a Flush!" << std::endl;
    }
    if (isFullHouse()) {
        std::cout << "The hand is a Full House!" << std::endl;
    }
    if (isFourOfAKind()) {
        std::cout << "The hand is a Four of a Kind!" << std::endl;
    }
    if (isStraightFlush()) {
        std::cout << "The hand is a Straight Flush!" << std::endl;
    }
}

HandType PokerHand::getHandType() const {
    if (isStraightFlush()) {
        return HandType::STRAIGHT_FLUSH;
    }
    if (isFourOfAKind()) {
        return HandType::FOUR_OF_A_KIND;
    }
    if (isFullHouse()) {
        return HandType::FULL_HOUSE;
    }
    if (isFlush()) {
        return HandType::FLUSH;
    }
    if (isStraight()) {
        return HandType::STRAIGHT;
    }
    if (isThreeOfAKind()) {
        return HandType::THREE_OF_A_KIND;
    }
    if (isTwoPair()) {
        return HandType::TWO_PAIR;
    }
    if (isPair()) {
        return HandType::PAIR;
    }
    return HandType::HIGH_CARD;
}

// 比较两手牌的大小
int PokerHand::compareHands(const std::vector<Card> &hand1, const std::vector<Card> &hand2) {
    HandType handType1 = PokerHand(hand1).getHandType();
    HandType handType2 = PokerHand(hand2).getHandType();

    // 比较牌型的大小
    if (handType1 > handType2) {
        return 1;  // hand1胜出
    } else if (handType1 < handType2) {
        return -1; // hand2胜出
    } else {
        // 牌型相同，按照规则逐个比较
        switch (handType1) {
            case HandType::HIGH_CARD: {
                // 比较高牌的大小，按照最高的牌逐个比较
                for (int i = 4; i >= 0; --i) {
                    Rank rank1 = hand1[i].getRank();
                    Rank rank2 = hand2[i].getRank();
                    if (rank1 > rank2) {
                        return 1;  // hand1胜出
                    } else if (rank1 < rank2) {
                        return -1; // hand2胜出
                    }
                }
                return 0;  // 平局
            }

            case HandType::PAIR: {
                // 比较对子的大小
                Rank pair1 = hand1[1].getRank();  // 获取对子的大小
                Rank pair2 = hand2[1].getRank();  // 获取对子的大小
                if (pair1 > pair2) {
                    return 1;  // hand1胜出
                } else if (pair1 < pair2) {
                    return -1; // hand2胜出
                } else {
                    // 对子大小相同，比较剩余的高牌
                    for (int i = 4; i >= 0; --i) {
                        Rank rank1 = hand1[i].getRank();
                        Rank rank2 = hand2[i].getRank();
                        if (rank1 > rank2) {
                            return 1;  // hand1胜出
                        } else if (rank1 < rank2) {
                            return -1; // hand2胜出
                        }
                    }
                    return 0;  // 平局
                }
            }

            case HandType::TWO_PAIR: {
                // 比较两对的大小
                std::vector<Rank> ranks1;
                std::vector<Rank> ranks2;

                // 获取两对的大小并排序
                for (int i = 0; i < 4; i += 2) {
                    ranks1.push_back(hand1[i].getRank());
                    ranks2.push_back(hand2[i].getRank());
                }
                std::sort(ranks1.rbegin(), ranks1.rend());
                std::sort(ranks2.rbegin(), ranks2.rend());

                // 比较较大的对子
                if (ranks1[0] > ranks2[0]) {
                    return 1;  // hand1胜出
                } else if (ranks1[0] < ranks2[0]) {
                    return -1; // hand2胜出
                }

                // 比较较小的对子
                if (ranks1[1] > ranks2[1]) {
                    return 1;  // hand1胜出
                } else if (ranks1[1] < ranks2[1]) {
                    return -1; // hand2胜出
                }

                // 对子相同，比较剩余的高牌
                Rank kicker1 = hand1[4].getRank();
                Rank kicker2 = hand2[4].getRank();
                if (kicker1 > kicker2) {
                    return 1;  // hand1胜出
                } else if (kicker1 < kicker2) {
                    return -1; // hand2胜出
                }

                return 0;  // 平局
            }

            case HandType::THREE_OF_A_KIND: {
                // 比较三条的大小
                Rank three1 = hand1[2].getRank();  // 获取三条的大小
                Rank three2 = hand2[2].getRank();  // 获取三条的大小
                if (three1 > three2) {
                    return 1;  // hand1胜出
                } else if (three1 < three2) {
                    return -1; // hand2胜出
                } else {
                    // 三条大小相同，比较剩余的高牌
                    for (int i = 4; i >= 0; --i) {
                        if (i == 2) continue;  // 跳过三条
                        Rank rank1 = hand1[i].getRank();
                        Rank rank2 = hand2[i].getRank();
                        if (rank1 > rank2) {
                            return 1;  // hand1胜出
                        } else if (rank1 < rank2) {
                            return -1; // hand2胜出
                        }
                    }
                    return 0;  // 平局
                }
            }

            case HandType::STRAIGHT: {
                // 比较顺子的大小，只需比较最大的一张牌
                Rank highCard1 = hand1[4].getRank();
                Rank highCard2 = hand2[4].getRank();
                if (highCard1 > highCard2) {
                    return 1;  // hand1胜出
                } else if (highCard1 < highCard2) {
                    return -1; // hand2胜出
                } else {
                    return 0;  // 平局
                }
            }

            case HandType::FLUSH: {
                // 比较同花的大小，按照最高的牌逐个比较
                for (int i = 4; i >= 0; --i) {
                    Rank rank1 = hand1[i].getRank();
                    Rank rank2 = hand2[i].getRank();
                    if (rank1 > rank2) {
                        return 1;  // hand1胜出
                    } else if (rank1 < rank2) {
                        return -1; // hand2胜出
                    }
                }
                return 0;  // 平局
            }

            case HandType::FULL_HOUSE: {
                // 比较葫芦的大小
                Rank three1 = hand1[2].getRank();  // 获取三条的大小
                Rank three2 = hand2[2].getRank();  // 获取三条的大小
                if (three1 > three2) {
                    return 1;  // hand1胜出
                } else if (three1 < three2) {
                    return -1; // hand2胜出
                } else {
                    Rank pair1 = hand1[4].getRank();  // 获取对子的大小
                    Rank pair2 = hand2[4].getRank();  // 获取对子的大小
                    if (pair1 > pair2) {
                        return 1;  // hand1胜出
                    } else if (pair1 < pair2) {
                        return -1; // hand2胜出
                    } else {
                        return 0;  // 平局
                    }
                }
            }

            case HandType::FOUR_OF_A_KIND: {
                // 比较四条的大小
                Rank four1 = hand1[2].getRank();  // 获取四条的大小
                Rank four2 = hand2[2].getRank();  // 获取四条的大小
                if (four1 > four2) {
                    return 1;  // hand1胜出
                } else if (four1 < four2) {
                    return -1; // hand2胜出
                } else {
                    // 四条大小相同，比较剩余的高牌
                    Rank kicker1 = hand1[0].getRank();
                    Rank kicker2 = hand2[0].getRank();
                    if (kicker1 > kicker2) {
                        return 1;  // hand1胜出
                    } else if (kicker1 < kicker2) {
                        return -1; // hand2胜出
                    } else {
                        return 0;  // 平局
                    }
                }
            }

            case HandType::STRAIGHT_FLUSH: {
                // 比较同花顺的大小，只需比较最大的一张牌
                Rank highCard1 = hand1[4].getRank();
                Rank highCard2 = hand2[4].getRank();
                if (highCard1 > highCard2) {
                    return 1;  // hand1胜出
                } else if (highCard1 < highCard2) {
                    return -1; // hand2胜出
                } else {
                    return 0;  // 平局
                }
            }
        }
    }
}


std::vector<Card> PokerHand::getBestHand(const std::vector<Card> &hand1, const std::vector<Card> &hand2) {
    std::vector<Card> allCards;
    allCards.reserve(7);

    // 将手中的两张牌和公共五张牌都添加到向量中
    for (const Card& card : hand1) {
        allCards.push_back(card);
    }
    for (const Card& card : hand2) {
        allCards.push_back(card);
    }

    //debug
    std::cout << "Hand 1: ";
    for (const Card& card : hand1) {
        std::cout << card.getRankString() << " of " << card.getSuitString() << " ";
    }
    std::cout << std::endl;

    std::cout << "Hand 2: ";
    for (const Card& card : hand2) {
        std::cout << card.getRankString() << " of " << card.getSuitString() << " ";
    }
    std::cout << std::endl;

    std::cout << "allCards : ";
    for (const Card& card : allCards) {
        std::cout << card.getRankString() << " of " << card.getSuitString() << " ";
    }
    std::cout << std::endl;


    // 将手中的两张牌和公共五张牌都添加到向量中
    for (int i = 0; i < 2; ++i) {
        allCards.push_back(hand1[i]);
    }
    for (int i = 0; i < 5; ++i) {
        allCards.push_back(hand2[i]);
    }

    // 尝试所有可能的组合并找到最佳手牌
    std::vector<Card> bestHand;
    std::vector<Card> tempHand;

    // 遍历所有的组合
    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            for (int k = j + 1; k < 5; ++k) {
                for (int l = k + 1; l < 6; ++l) {
                    for (int m = l + 1; m < 7; ++m) {
                        tempHand.clear();
                        // 将当前组合中的五张牌添加到临时手牌中
                        tempHand.push_back(allCards[i]);
                        tempHand.push_back(allCards[j]);
                        tempHand.push_back(allCards[k]);
                        tempHand.push_back(allCards[l]);
                        tempHand.push_back(allCards[m]);
                        // 如果临时手牌是更好的手牌，则更新最佳手牌
                        if (isBetterHand(tempHand, bestHand)) {
                            bestHand = tempHand;
                        }
                    }
                }
            }
        }
    }
    return bestHand;
}


bool PokerHand::isBetterHand(const std::vector<Card> &hand1, const std::vector<Card> &hand2) {
    PokerHand pokerHand1(hand1);
    PokerHand pokerHand2(hand2);

    // debug
    std::cout << "Comparing hand1 and hand2..." << std::endl;

    std::cout << "Hand 1: ";
    for (const Card& card : hand1) {
        std::cout << card.getRankString() << " of " << card.getSuitString() << " ";
    }
    std::cout << std::endl;

    std::cout << "Hand 2: ";
    for (const Card& card : hand2) {
        std::cout << card.getRankString() << " of " << card.getSuitString() << " ";
    }
    std::cout << std::endl;

    HandType type1 = pokerHand1.getHandType();
    HandType type2 = pokerHand2.getHandType();

    if (type1 > type2) {
        return true;
    } else if (type1 < type2) {
        return false;
    }

    // 如果手牌类型相同，根据不同的牌型规则进行比较
    switch (type1) {
        case HandType::STRAIGHT_FLUSH:
        case HandType::STRAIGHT:
        case HandType::FLUSH:
        case HandType::HIGH_CARD:
            // 直接比较最高牌的牌值
            return hand1[0].getRank() > hand2[0].getRank();
        case HandType::FOUR_OF_A_KIND:
        case HandType::THREE_OF_A_KIND:
            // 比较牌值较大的那组牌的牌值
            return hand1[2].getRank() > hand2[2].getRank();
        case HandType::FULL_HOUSE:
        case HandType::TWO_PAIR:
            // 先比较三张牌的牌值，再比较两张牌的牌值
            if (hand1[2].getRank() != hand2[2].getRank()) {
                return hand1[2].getRank() > hand2[2].getRank();
            } else {
                return hand1[0].getRank() > hand2[0].getRank();
            }
        case HandType::PAIR:
            // 先比较对子的牌值，再比较剩余的三张牌的牌值
            if (hand1[1].getRank() != hand2[1].getRank()) {
                return hand1[1].getRank() > hand2[1].getRank();
            } else {
                for (int i = 4; i >= 0; --i) {
                    if (hand1[i].getRank() != hand1[1].getRank() && hand2[i].getRank() != hand2[1].getRank()) {
                        if (hand1[i].getRank() != hand2[i].getRank()) {
                            return hand1[i].getRank() > hand2[i].getRank();
                        }
                    }
                }
                // 如果两个手牌完全相同，则返回false
                return false;
            }
    }
}
