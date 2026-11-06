#include "algorithms.h"

void mergeSort(vector<PlayerStats*>& a, int key) {
    if (a.size() <= 1) return;

    size_t mid = a.size() / 2;
    vector<PlayerStats*> left(a.begin(), a.begin() + mid);
    vector<PlayerStats*> right(a.begin() + mid, a.end());

    mergeSort(left, key);
    mergeSort(right, key);

    size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        bool takeRight = false;

        switch (key) {
            case 1:  takeRight = right[j]->xp   > left[i]->xp;   break;
            case 2:  takeRight = right[j]->wins > left[i]->wins; break;
            case 3:  takeRight = right[j]->kd   > left[i]->kd;   break;
            case 4:  takeRight = right[j]->username < left[i]->username; break;
            default: break;
        }

        if (takeRight) a[k++] = right[j++];
        else           a[k++] = left[i++];
    }
    while (i < left.size())  a[k++] = left[i++];
    while (j < right.size()) a[k++] = right[j++];
}

void quicksort(vector<PlayerStats*>& a, int key) {
    quicksortHelper(a,0,a.size() -1, key);
}

void quicksortHelper(vector<PlayerStats*>& a,int low, int high, int key)
{
    if (low < high) {
        //selecting pivot
        int pivotPosition = low + rand() % (high - low + 1);
        PlayerStats* temp = a[low];
        a[low] = a[pivotPosition];
        a[pivotPosition] = temp;

        PlayerStats* pivot = a[low];
        int up = low;
        int down = high;

        while (up < down) {
            for (int i = up; i < high; i++) {
                if (compareValues(pivot,a[up],key)) {
                    break;
                }
                up++;
            }
            for (int i = high; i > low; i--) {
                if(compareValues(a[down],pivot,key)) {
                    break;
                }
                down--;
            }
            if (up < down) {
                PlayerStats* player = a[up];
                a[up] = a[down];
                a[down] = player;
            }

        }
        PlayerStats* player = a[low];
        a[low] = a[down];
        a[down] = player;
        pivotPosition = down;

        quicksortHelper(a, low, pivotPosition-1, key);
        quicksortHelper(a, pivotPosition+1, high, key);
    }
}

bool compareValues(PlayerStats* a, PlayerStats* b, int key) {
    switch (key) {
        case 1:  return a->xp > b->xp;
        case 2:  return a->wins > b->wins;
        case 3:  return a->kd > b->kd;
        case 4:  return a->username > b->username;
    }
}
