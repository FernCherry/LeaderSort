#pragma once
#include <vector>

struct PlayerStats;

// key: 1 = xp, 2 = wins, 3 = kd (high to low), 4 = username (A to Z)
void mergeSort(std::vector<PlayerStats*>& a, int key);
void quicksort(std::vector<PlayerStats*>& a, int key);
void quicksortHelper(std::vector<PlayerStats*>& a,int low, int high, int key);
bool compareValues(PlayerStats* a, PlayerStats* b, int key);
