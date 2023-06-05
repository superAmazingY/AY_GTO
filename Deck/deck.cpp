#include "deck.h"
#include <algorithm>
#include <chrono>

Deck::Deck() {
    // 初始化一副完整的扑克牌
    for (int suit = static_cast<int>(Suit::CLUBS); suit <= static_cast<int>(Suit::SPADES); ++suit) {
        for (int rank = static_cast<int>(Rank::ACE); rank <= static_cast<int>(Rank::KING); ++rank) {
            cards.emplace_back(static_cast<Suit>(suit), static_cast<Rank>(rank));
        }
    }

    // 使用当前时间作为种子值初始化随机数引擎
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    randomEngine = std::default_random_engine(seed);
}

void Deck::shuffle() {
    //洗牌
    std::shuffle(cards.begin(), cards.end(), randomEngine);
}

Card Deck::dealCard() {
    //发牌
    Card card = cards.back();
    cards.pop_back();
    return card;
}

int Deck::getNumCards() const {
    //返回牌堆数量
    return cards.size();
}
