cmake_minimum_required(VERSION 3.24)
project(AY_GTO)

set(CMAKE_CXX_STANDARD 17)

add_executable(AY_GTO main.cpp Card/card.cpp Deck/deck.cpp Deck/deck.h pokerHand/pokerhand.cpp pokerHand/pokerhand.h)
