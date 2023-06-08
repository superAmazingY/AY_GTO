#include "Card/card.h"
#include "Deck/deck.h"
#include "pokerHand/pokerhand.h"

int main() {
    Deck deck;
    deck.shuffle();
    std::cout << "Dealing cards..." << std::endl;

    std::vector<Card> player1;
    std::vector<Card> player2;
    std::vector<Card> commonCard;

    // 发牌给玩家1
    for (int i = 0; i < 2; i++) {
        Card card1 = deck.dealCard();
        player1.push_back(card1);
        std::cout << "Dealt card 1: " << card1.getRankString() << " of " << card1.getSuitString() << std::endl;
    }

    // 发牌给玩家2
    for (int i = 0; i < 2; i++) {
        Card card2 = deck.dealCard();
        player2.push_back(card2);
        std::cout << "Dealt card 2: " << card2.getRankString() << " of " << card2.getSuitString() << std::endl;
    }

    // 发公共牌
    for (int i = 0; i < 5; i++) {
        Card card3 = deck.dealCard();
        commonCard.push_back(card3);
        std::cout << "Dealt card 3: " << card3.getRankString() << " of " << card3.getSuitString() << std::endl;
    }


    PokerHand pokerHand1(player1);
    PokerHand pokerHand2(player2);

    // 获取每个玩家的最佳手牌
    std::vector<Card> player1BestHand = PokerHand::getBestHand(commonCard, player1);
    std::vector<Card> player2BestHand = PokerHand::getBestHand(commonCard, player2);

    PokerHand pokerHand3(player1BestHand);
    PokerHand pokerHand4(player2BestHand);
    // 打印最佳牌型的类型
    pokerHand3.printHandType();
    pokerHand4.printHandType();

    // 比较手牌大小
    int result = PokerHand::compareHands(player1BestHand, player2BestHand);

    if (result == 1) {
        std::cout << "Hand 1 wins!" << std::endl;
    } else if (result == -1) {
        std::cout << "Hand 2 wins!" << std::endl;
    } else {
        std::cout << "It's a tie!" << std::endl;
    }
    return 0;
}
