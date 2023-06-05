#include <algorithm>
#include "pokerhand.h"

PokerHand::PokerHand(const std::vector<Card>& hand) : hand(hand) {}

bool PokerHand::isHighCard() const {
    // 高牌：没有符合其他牌型的组合
    // 逻辑：排除其他牌型的情况即可
    return !isPair() && !isTwoPair() && !isThreeOfAKind() && !isStraight() && !isFlush() && !isFullHouse() && !isFourOfAKind() && !isStraightFlush();
}

bool PokerHand::isPair() const {
    // 对子：有两张相同点数的牌
    // 逻辑：统计每个点数的牌的数量，如果有两张点数相同的牌，则为对子
    std::vector<Rank> ranks;
    for (const Card& card : hand) {
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
    for (const Card& card : hand) {
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
    for (const Card& card : hand) {
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
    for (const Card& card : hand) {
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
    for (const Card& card : hand) {
        suits.push_back(card.getSuit());
    }
    std::sort(suits.begin(), suits.end());

    for (size_t i = 0; i < suits.size() - 1; ++i) {
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
    for (const Card& card : hand) {
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
    for (const Card& card : hand) {
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

Rank PokerHand::getHighestRank() const {
    Rank highestRank = Rank::UNKNOWN;
    for (const Card& card : hand) {
        if (card.getRank() > highestRank) {
            highestRank = card.getRank();
        }
    }
    return highestRank;
}

Rank PokerHand::getRankAtPosition(int position) const {
    if (position < 0 || position >= hand.size()) {
        // 处理无效位置的情况，例如越界等
        // 在此处抛出异常或返回一个特定值
    }
    return hand[position].getRank();
}


// 比较两手牌的大小
int PokerHand::compareHands(const PokerHand& hand1, const PokerHand& hand2) {
    HandType handType1 = hand1.getHandType();
    HandType handType2 = hand2.getHandType();

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
                    Rank rank1 = hand1.getRankAtPosition(i);
                    Rank rank2 = hand2.getRankAtPosition(i);
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
                Rank pair1 = hand1.getRankAtPosition(1);  // 获取对子的大小
                Rank pair2 = hand2.getRankAtPosition(1);  // 获取对子的大小
                if (pair1 > pair2) {
                    return 1;  // hand1胜出
                } else if (pair1 < pair2) {
                    return -1; // hand2胜出
                } else {
                    // 对子大小相同，比较剩余的高牌
                    for (int i = 4; i >= 0; --i) {
                        Rank rank1 = hand1.getRankAtPosition(i);
                        Rank rank2 = hand2.getRankAtPosition(i);
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
                Rank highestPair1 = hand1.getRankAtPosition(3);  // 获取第一对的大小
                Rank highestPair2 = hand2.getRankAtPosition(3);  // 获取第一对的大小
                if (highestPair1 > highestPair2) {
                    return 1;  // hand1胜出
                } else if (highestPair1 < highestPair2) {
                    return -1; // hand2胜出
                } else {
                    // 第一对大小相同，比较第二对
                    Rank secondPair1 = hand1.getRankAtPosition(1);  // 获取第二对的大小
                    Rank secondPair2 = hand2.getRankAtPosition(1);  // 获取第二对的大小
                    if (secondPair1 > secondPair2) {
                        return 1;  // hand1胜出
                    } else if (secondPair1 < secondPair2) {
                        return -1; // hand2胜出
                    } else {
                        // 两对大小都相同，比较最高的单张牌
                        Rank kicker1 = hand1.getRankAtPosition(4);  // 获取最高的单张牌大小
                        Rank kicker2 = hand2.getRankAtPosition(4);  // 获取最高的单张牌大小
                        if (kicker1 > kicker2) {
                            return 1;  // hand1胜出
                        } else if (kicker1 < kicker2) {
                            return -1; // hand2胜出
                        } else {
                            return 0;  // 平局
                        }
                    }
                }
            }

            case HandType::THREE_OF_A_KIND: {
                // 比较三条的大小
                Rank triplet1 = hand1.getRankAtPosition(2);  // 获取三条的大小
                Rank triplet2 = hand2.getRankAtPosition(2);  // 获取三条的大小
                if (triplet1 > triplet2) {
                    return 1;  // hand1胜出
                } else if (triplet1 < triplet2) {
                    return -1; // hand2胜出
                } else {
                    // 三条大小相同，比较剩余两张牌的大小
                    std::vector<Rank> remaining1;
                    std::vector<Rank> remaining2;
                    for (int i = 0; i < 5; ++i) {
                        Rank rank1 = hand1.getRankAtPosition(i);
                        Rank rank2 = hand2.getRankAtPosition(i);
                        if (rank1 != triplet1) {
                            remaining1.push_back(rank1);
                        }
                        if (rank2 != triplet2) {
                            remaining2.push_back(rank2);
                        }
                    }
                    std::sort(remaining1.rbegin(), remaining1.rend());
                    std::sort(remaining2.rbegin(), remaining2.rend());
                    for (int i = 0; i < 2; ++i) {
                        if (remaining1[i] > remaining2[i]) {
                            return 1;  // hand1胜出
                        } else if (remaining1[i] < remaining2[i]) {
                            return -1; // hand2胜出
                        }
                    }
                    return 0;  // 平局
                }
            }

            case HandType::STRAIGHT: {
                // 比较顺子的大小
                Rank highestRank1 = hand1.getHighestRank();
                Rank highestRank2 = hand2.getHighestRank();
                if (highestRank1 > highestRank2) {
                    return 1;  // hand1胜出
                } else if (highestRank1 < highestRank2) {
                    return -1; // hand2胜出
                } else {
                    return 0;  // 平局
                }
            }

            case HandType::FLUSH: {
                // 比较同花的大小，按照最高的牌逐个比较
                for (int i = 4; i >= 0; --i) {
                    Rank rank1 = hand1.getRankAtPosition(i);
                    Rank rank2 = hand2.getRankAtPosition(i);
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
                Rank triplet1 = hand1.getRankAtPosition(2);  // 获取三条的大小
                Rank triplet2 = hand2.getRankAtPosition(2);  // 获取三条的大小
                if (triplet1 > triplet2) {
                    return 1;  // hand1胜出
                } else if (triplet1 < triplet2) {
                    return -1; // hand2胜出
                } else {
                    Rank pair1 = hand1.getRankAtPosition(1);  // 获取对子的大小
                    Rank pair2 = hand2.getRankAtPosition(1);  // 获取对子的大小
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
               Rank quad1 = hand1.getRankAtPosition(2);  // 获取四条的大小
                Rank quad2 = hand2.getRankAtPosition(2);  // 获取四条的大小
                if (quad1 > quad2) {
                    return 1;  // hand1胜出
                } else if (quad1 < quad2) {
                    return -1; // hand2胜出
                } else {
                    // 四条大小相同，比较剩余的一张牌
                    Rank kicker1 = hand1.getRankAtPosition(4);  // 获取剩余的一张牌大小
                    Rank kicker2 = hand2.getRankAtPosition(4);  // 获取剩余的一张牌大小
                    if (kicker1 > kicker2) {
                        return 1;  // hand1胜出
                    } else if (kicker1 < kicker2) {
                        return -1; // hand2胜出
                    } else {
                        return 0;  // 平局
                    }
                }
            }

            case HandType::STRAIGHT_FLUSH:{
                // 顺子和同花顺比较规则与顺子相同，因为同花顺和皇家同花顺不存在相同牌型的情况
                Rank highestRank1 = hand1.getHighestRank();
                Rank highestRank2 = hand2.getHighestRank();
                if (highestRank1 > highestRank2) {
                    return 1;  // hand1胜出
                } else if (highestRank1 < highestRank2) {
                    return -1; // hand2胜出
                } else {
                    return 0;  // 平局
                }
            }
        }
    }
}

std::vector<Card> PokerHand::getBestHand(const PokerHand& hand1, const PokerHand& hand2) {
    std::vector<Card> allCards;
    allCards.reserve(7);

    // 将手中的两张牌和公共五张牌都添加到向量中
    for (int i = 0; i < 2; ++i) {
        allCards.push_back(hand1.getCardAtPosition(i));
    }
    for (int i = 0; i < 5; ++i) {
        allCards.push_back(hand2.getCardAtPosition(i));
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

bool PokerHand::isBetterHand(const std::vector<Card>& hand1, const std::vector<Card>& hand2) const {
    PokerHand pokerHand1(hand1);
    PokerHand pokerHand2(hand2);

    HandType type1 = pokerHand1.getHandType();
    HandType type2 = pokerHand2.getHandType();

    if (type1 > type2) {
        return true;
    } else if (type1 < type2) {
        return false;
    }
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
            }
            return false;

        default:
            // 无效手牌类型，可以根据实际情况进行处理
            return false;
    }
}

Card PokerHand::getCardAtPosition(int position) const {
    // 根据实际情况实现获取指定位置的牌的逻辑
    // 返回对应位置的牌
    if (position < 0 || position >= hand.size()) {
        // 位置无效，可以抛出异常或者进行其他处理
        // 这里假设返回一个无效的牌
        return Card(Suit::UNKNOWN, Rank::UNKNOWN);
    }
    return hand[position];
}