#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

struct PlayerStats {
	string username;
	int xp;
	int wins;
	float kd;

	PlayerStats(int random_number) {
		username = "default_name" + to_string(random_number);
		wins = kd = 0;
		xp = (random_number * 37 + 11) % 100; // cool hash
	}
};

// key: 1 = xp, 2 = wins, 3 = kd (high to low), 4 = username (A to Z)
void mergeSort(vector<PlayerStats*>& a, int key);
void quicksort(vector<PlayerStats*>& a, int key);
void quicksortHelper(vector<PlayerStats*>& a,int low, int high, int key);
bool compareValues(PlayerStats* a, PlayerStats* b, int key);
