#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string.h>
#include <string>
#include <vector>

struct Card {
  std::string suite, title;
};
struct Player {
  Player(std::string name) : name(name){};
  std::vector<Card> pack;
  void play(int pos, std::vector<Card> &board) {
    int r = pos - 1;
    if (board.size() == 0 && pack.data()[r].title != "3" &&
        pack.data()[r].title != "2") {
      board.emplace_back(pack.at(r));
      lastPlayed = pack.at(r);
      std::cout << lastPlayed.title << " of " << lastPlayed.suite << std::endl;
      rearrange(r);
      std::cout << pack.size();
    } else if (board.size() != 0 &&
               board.data()[board.size()].suite == pack.data()[r].suite) {
      board.emplace_back(pack.at(r));
      rearrange(r);
    } else {
      std::cout << "Apigwe fine\n";
    }
  }
  std::string getName() { return name; }

private:
  void rearrange(int r) {
    for (int i{r}; i < pack.size() - 1; i++) {
      pack.at(i) = pack.at(i + 1);
    }
    pack.pop_back();
  }
  Card lastPlayed;
  std::string name;
};
void shuffle(std::vector<Card> &Deck, int num) {
  int k = 0;
  while (k < num) {
    int s = rand() % Deck.size(), y = rand() % Deck.size();

    std::string tempSuite = Deck[s].suite, tempTitle = Deck[s].title;
    Deck[s].suite = Deck[y].suite;
    Deck[s].title = Deck[y].title;
    Deck[y].title = tempTitle;
    Deck[y].suite = tempSuite;
    k++;
  }
}

void printDeck(std::vector<Card> &Deck, int num) {
  for (int i = 0; i < num; i++) {
    std::cout << Deck[i].title << " of " << Deck[i].suite << std::endl;
  }
}

void pickCard(std::vector<Card> &Deck, Player *player, int cards) {
  int s = Deck.size();
  for (int i = 0; i < cards; i++) {
    player->pack.push_back(Card{Deck[0].suite, Deck[0].title});
    std::cout << player->getName() << " " << player->pack[i].title << " of "
              << player->pack[i].suite << std::endl;
    for (int j{0}; j < s - 1; j++) {
      Deck.at(j) = Deck.at(j + 1);
    }
    s--;
  }
}
bool checkWin(Player *player) { return true; }
int main() {
  const std::string suite[4] = {"Spades", "Hearts", "Diamonds", "Clubs"};
  const std::string title[13] = {"Ace", "2", "3",  "4",    "5",     "6",   "7",
                                 "8",   "9", "10", "Jack", "Queen", "King"};
  Player player[4] = {{"Player 1"}, {"Player 2"}, {"Player 3"}, {"Player 4"}};
  std::vector<Card> Deck;
  int n = 0;
  std::vector<Card> board;
  while (Deck.size() < 52) {
    for (int i{0}; i < 4; i++) {
      for (int j{0}; j < 13; j++) {
        Deck.emplace_back(Card{suite[i], title[j]});
      }
    }
  }
  for (int i = 0; i < 53; i++) {
    shuffle(Deck, 120);
  }
  // printDeck(Deck, Deck.size());
  for (int i{0}; i < 4; i++) {
    pickCard(Deck, &player[i], 4);
  }
  player[0].play(2, board);
}
