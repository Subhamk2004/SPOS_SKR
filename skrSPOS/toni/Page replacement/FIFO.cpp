#include <bits/stdc++.h>
using namespace std;

void fifoPage(const vector<int>& pg, int pn, int fn) {
    vector<int> fr;  // Frame
    queue<int> fifoQueue;
    int pageFaults = 0;

    vector<int> pageFaultsArray(pn, 0);
    vector<int> pageHitsArray(pn, 0);

    for (int i = 0; i < pn; i++) {
        int currentPage = pg[i];

        // Check if the page is already in the frame (page hit)
        if (find(fr.begin(), fr.end(), currentPage) == fr.end()) {
            // Page fault
            pageFaults++;
            pageFaultsArray[i] = 1;  // Mark as page fault

            if (fr.size() < fn) {
                fr.push_back(currentPage);
                fifoQueue.push(currentPage);
            } else {
                int replacedPage = fifoQueue.front();
                fifoQueue.pop();
                
                for(int j = 0; j < fr.size(); j++){
                    if(fr[j] == replacedPage){
                        fr[j] = currentPage;
                    }
                }
                fifoQueue.push(currentPage);
            }
        } else {
            pageHitsArray[i] = 1;  // Mark as page hit
        }

        cout << "Page " << currentPage << " is in the frame. Frame Contents: ";
        for (int page : fr) {
            cout << page << " ";
        }
        cout << endl;
    }

    cout << "\nPage Faults Array: ";
    for (int fault : pageFaultsArray) {
        cout << fault << " ";
    }
    cout << "\nPage Hits Array: ";
    for (int hit : pageHitsArray) {
        cout << hit << " ";
    }
    cout << endl;

}

int main() {
    int pn, fn;
    cout << "Enter the number of pages: ";
    cin >> pn;
    vector<int> pg(pn);

    cout << "Enter the page numbers:" << endl;
    for (int i = 0; i < pn; i++) {
        cin >> pg[i];
    }

    cout << "Enter the frame size: ";
    cin >> fn;

    fifoPage(pg, pn, fn);

    return 0;
}

//This C++ program implements the FIFO (First-In, First-Out) page replacement algorithm for memory management. The goal of the algorithm is to simulate how a page fault occurs when a page is accessed that is not currently in memory (a frame). It replaces the oldest page in memory when a new page needs to be loaded, following the FIFO policy.

//Key Concepts

    //Page Fault: When a requested page is not found in the frame.
    //Page Hit: When the requested page is already in the frame (no replacement is needed).
   // FIFO (First-In-First-Out): The page that has been in the frame the longest is replaced when a new page needs to //be loaded.
   
// Input:
//Pages: 1, 2, 3, 4, 1, 2, 5
//Frame size: 3

//Step-by-step:
//1. Page 1: [1] - Fault (frame not full)
//2. Page 2: [1,2] - Fault (frame not full)
//3. Page 3: [1,2,3] - Fault (frame now full)
//4. Page 4: [4,2,3] - Fault (replaced 1 as it was oldest)
//5. Page 1: [4,2,1] - Fault (replaced 3)
//6. Page 2: [4,2,1] - Hit (2 already present)
//7. Page 5: [5,2,1] - Fault (replaced 4)
