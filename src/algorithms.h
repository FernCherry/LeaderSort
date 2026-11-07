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

	PlayerStats(string username_, int xp_, float kd_, int wins_) {
		username = username_; xp = xp_; kd = kd_; wins = wins_;
	}
};

// key: 1 = xp, 2 = wins, 3 = kd (high to low), 4 = username (A to Z)
void mergeSort(vector<PlayerStats*>& a, int key);
void quicksort(vector<PlayerStats*>& a, int key);
void quicksortHelper(vector<PlayerStats*>& a,int low, int high, int key);
bool compareValues(PlayerStats* a, PlayerStats* b, int key);
