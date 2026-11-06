#include <vector>
#include <iostream>
#include "json.hpp"
#include "LeaderSortUI.h"
#include "fstream"
using namespace std;

using json = nlohmann::json;

string generateUser(vector<string> firstnames, vector<string> secondnames, int num)
{
    int randIndex1 = rand() % firstnames.size();
    int randIndex2 = rand() % secondnames.size();
    string player = firstnames[randIndex1] + secondnames[randIndex2] + to_string(num);

    return player;
}

int main() {
    vector<string> firstnames =
        {
        "Apple","Super", "Banana", "Pineapple", "Awesome", "Grape", "Blueberry", "Quick", "Slow",
        "Guava", "Orange", "Millionaire", "Carrot", "Shadow", "Bitter", "Sweet", "Big", "Small",
        "Nimble", "Peter", "John", "Jim", "Air"
    };
    vector<string> secondnames = {
        "Tiger", "Lion", "Cat", "Dog", "Mouse", "Ox", "Birds", "Pheonix","Goat", "Bunny", "Rabbit",
        "Fire"
    };

    json players = json::array();
    for (int i = 0; i < 120000; i++) {
        players.push_back(
    {
    {"username", generateUser(firstnames, secondnames, rand() % 12345)},
    {"wins", rand() % 500},
    {"xp", rand() % 100000000},
    {"kd", (float)(rand() % 1000) / 100.0}
        });
    }
    std::ofstream file("assets/players.json");
    file << players.dump();
}



