cmake_minimum_required(VERSION 3.9)
project(Blackjack)

set(CMAKE_CXX_STANDARD 11)

add_executable(Blackjack main.cpp Card.cpp Card.h DeckStack.cpp DeckStack.h Player.cpp Player.h Game.cpp Game.h)