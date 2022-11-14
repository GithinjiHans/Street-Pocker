#include <algorithm>
#include <arpa/inet.h>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

struct Card {
  std::string suite, title;
};
struct Player {
  Player(std::string name) : name(name){};
  std::vector<Card> pack;
  void play(int pos, std::vector<Card> &board) {
    int r = pos - 1;
    if (r < pack.size() && r >= 0) {
      if (board.size() == 0 && pack.data()[r].title != "3" &&
          pack.data()[r].title != "2") {
        board.emplace_back(pack.at(r));
        lastPlayed = pack.at(r);
        std::cout << lastPlayed.title << " of " << lastPlayed.suite
                  << std::endl;
        rearrange(r);
      } else if (board.data()[board.size() - 1].suite == pack.data()[r].suite ||
                 board.data()[board.size() - 1].title == pack.data()[r].title) {
        board.emplace_back(pack.at(r));
        rearrange(r);
      } else {
        std::cout << "Apigwe fine\n";
        std::cout << pack.data()[r].suite << pack.data()[r].title << std::endl;
      }
    } else {
      std::cout << "Invalid position\n";
    }
  }
  std::string getName() { return name; }
  Card getLastPlayed() { return lastPlayed; }

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
bool checkWin(Player *player) {
  if (player->pack.size() == 0 && player->getLastPlayed().title != "King" &&
      player->getLastPlayed().title != "Jack" &&
      player->getLastPlayed().title != "Queen" &&
      player->getLastPlayed().title != "2" &&
      player->getLastPlayed().title != "3") {
    return true;
  } else {
    return false;
  }
}

void rules(std::vector<Card> &board) {
  Card kadi = board.back();
  if (kadi.title == "Queen") {

  } else if (kadi.title == "Ace") {
    if (kadi.suite == "Spades") {
      char input[1024];
      std::string suite, title;

    } else {
    }
  } else if (kadi.title == "2" || kadi.title == "3") {

  } else if (kadi.title == "Jack") {
  }
}

void addPlayer(std::vector<Player> &players, std::string name, int cards,
               std::vector<Card> &Deck) {
  players.emplace_back(Player(name));
  pickCard(Deck, &players.back(), cards);
}

int main() {
  bool gameOver = false;
  bool turn = true;
  char input[1024];
  int pos;
  const std::string suite[4] = {"Spades", "Hearts", "Diamonds", "Clubs"};
  const std::string title[13] = {"Ace", "2", "3",  "4",    "5",     "6",   "7",
                                 "8",   "9", "10", "Jack", "Queen", "King"};
  std::vector<Player> players;
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
  int sock = socket(AF_INET6, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cout << "Could not create socket\n";
  }
  int port = 8000;
  struct sockaddr_in6 server;
  server.sin6_family = AF_INET6;
  server.sin6_addr = in6addr_any;
  server.sin6_port = htons(port);
  if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
    std::cout << "Bind failed\n";
    return 1;
  }
  listen(sock, 6);
  std::cout << "Waiting for incoming connections...\n";
  int c = sizeof(struct sockaddr_in6);
  struct sockaddr_in6 client;
  int client_sock = accept(sock, (struct sockaddr *)&client, (socklen_t *)&c);
  if (client_sock < 0) {
    std::cout << "Accept failed\n";
  }
  std::cout << "Connection accepted\n";
  // send a message to the client welcome to the game
  char client_message[2000];
  std::string welcome = "A new client has joined the game";
  // receive a message from the client
  memset(client_message, 0, sizeof(client_message));
  recv(client_sock, client_message, 2000, 0);
  std::string name = strtok(client_message, " "),cards = strtok(NULL, " ");
}
// commands:
// play <card_position>
// pick <cards>
