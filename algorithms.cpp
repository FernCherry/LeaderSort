#include "algorithms.h"
#include "LeaderSortUI.h"   // full PlayerStats definition

using namespace std;

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