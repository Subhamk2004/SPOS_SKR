#include <iostream>
#include <vector>
using namespace std;

void firstFit(int blockSize[], int m, int processSize[], int n) {
    vector<int> allocation(n, -1); // Array to store allocation of each process

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j+1; 
                blockSize[j] -= processSize[i]; 
                break; 
            }
        }
    }

    cout << "Process No.\tProcess Size\tBlock No." << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t\t" << processSize[i] << "\t\t" << allocation[i] << endl;
    }

}

int main() {
    int m, n;

    cout << "Enter the number of blocks and processes: ";
    cin >> m >> n;

    int processSize[n], blockSize[m];

    cout << "Enter the sizes of each process: ";
    for (int i = 0; i < n; i++) {
        cin >> processSize[i];
    }

    cout << "Enter the sizes of each block: ";
    for (int i = 0; i < m; i++) {
        cin >> blockSize[i];
    }

    firstFit(blockSize, m, processSize, n);

    return 0;
}

//The program allocates memory to processes based on the First-Fit strategy, which finds the first available block large enough for each process
