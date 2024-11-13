#include <iostream>
#include <vector>

using namespace std;

void bestFit(int blockSize[], int m, int processSize[], int n) {
    vector<int> allocation(n, -1); // Array to store allocation of each process

    // Iterate through each process and find the best fit block
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[bestIdx] > blockSize[j]) {
                    bestIdx = j;
                }
            }
        }

        // If a suitable block was found, allocate it
        if (bestIdx != -1) {
            allocation[i] = bestIdx + 1;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "Process No\tProcess Size\tBlock No." << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << processSize[i] << "\t\t" << allocation[i] << endl;
    }
}

int main() {
    int m, n;

    cout << "Enter the number of blocks and processes: ";
    cin >> m >> n;

    int blockSize[m], processSize[n];

    cout << "Enter the sizes of each process: ";
    for (int i = 0; i < n; i++) {
        cin >> processSize[i];
    }

    cout << "Enter the sizes of each block: ";
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
    }

    bestFit(blockSize, m, processSize, n);

    return 0;
}

// The program allocates memory blocks to processes using the Best-Fit strategy.
// It finds the smallest block that can fit each process and allocates it, 
// block size - process size should be minimum
