#include <iostream>
#include <vector>
using namespace std;

void worstFit(vector<int>& blockSize, int m, const vector<int>& processSize, int n) {
    vector<int> allocation(n, -1); // Initialize allocation array with -1 (indicating no allocation)

    // Loop over each process to allocate memory
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
      
        if (worstIdx != -1) {
            allocation[i] = worstIdx + 1;
            blockSize[worstIdx] -= processSize[i]; 
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

    worstFit(blockSize, m, processSize, n);

    return 0;
}

// opposite of best fit
//each process is allocated to the largest block available that can accommodate its size. 
