#include <iostream>
#include <vector>
using namespace std;

void nextFit(vector<int>& blockSize, int m, const vector<int>& processSize, int n) {
    vector<int> allocation(n, -1); // Initialize allocation array with -1 (no allocation)
    int j = 0; // Start from the first block

    for (int i = 0; i < n; i++) {
        // Search for the next block with enough space in a circular manner
        int count = 0;
        while (count < m) { // Limit search to m blocks to prevent infinite loop
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j + 1; // Allocate block j to process i (1-based index)
                blockSize[j] -= processSize[i]; // Reduce available memory in block j
                break; // Move to the next process
            }
            j = (j + 1) % m; // Move to the next block, looping back if necessary
            count++;
        }
    }

    cout << "Process no.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << processSize[i] << "\t\t" << allocation[i] << endl;
    }
}

int main() {
    int m, n;
    cout << "Enter the number of blocks and processes: ";
    cin >> m >> n;

    vector<int> blockSize(m), processSize(n);

    cout << "Enter the sizes of each block:\n";
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
    }

    cout << "Enter the sizes of each process:\n";
    for (int i = 0; i < n; i++) {
        cin >> processSize[i];
    }

    nextFit(blockSize, m, processSize, n);

    return 0;
}



// This C++ program uses the Next-Fit memory allocation strategy, where each process is assigned to the next available block with sufficient space, starting from the block just after the last allocation.

//If a process cannot be allocated to any block, it remains unallocated.
