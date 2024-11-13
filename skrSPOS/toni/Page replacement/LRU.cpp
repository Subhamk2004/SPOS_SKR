#include <bits/stdc++.h>
using namespace std;

void pageFaults(const vector<int>& pages, int capacity) {
    vector<int> frames;                      // Stores pages in memory
    deque<int> order;                        // Tracks LRU order
    int pageFaults = 0;                      // Count of page faults
    vector<int> pageHits(pages.size(), 0);   // 1 for hit, 0 for miss
    vector<int> pageFaultsArr(pages.size(), 0); // 1 for fault, 0 for hit

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];

        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            pageFaults++;
            pageFaultsArr[i] = 1;  // Mark as page fault

            // If frames are at capacity, replace the least recently used page
            if (frames.size() == capacity) {
                int lru = order.front();  // Get the least recently used page
                order.pop_front();
                
                for(int j = 0; j < frames.size(); j++){
                    if(frames[j] == lru) frames[j] = page;
                }
            } else {
                // If there's space, add the page to frames
                frames.push_back(page);
            }

            // Mark the new page as recently used
            order.push_back(page);
        } else {
            // Page hit
            pageHits[i] = 1;  // Mark as page hit

            // Update LRU order
            order.erase(find(order.begin(), order.end(), page));
            order.push_back(page);
        }

        // Display current frame contents
        cout << "Frame after accessing page " << page << ": ";
        for (int p : frames) cout << p << " ";
        cout << endl;
    }

    // Display page hits and faults arrays
    cout << "\nPage Hits Array: ";
    for (int hit : pageHits) cout << hit << " ";
    cout << "\nPage Faults Array: ";
    for (int fault : pageFaultsArr) cout << fault << " ";
    
    // Total page faults
    cout << "\nTotal Page Faults: " << pageFaults << endl;
}

int main() {
    int n, capacity;

    cout << "Enter the number of pages: ";
    cin >> n;
    vector<int> pages(n);

    cout << "Enter the page numbers:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter the number of frames: ";
    cin >> capacity;

    pageFaults(pages, capacity);

    return 0;
}

//Uses deque instead of queue to allow removal from any position
//Updates order on both hits and faults
//Removes pages based on actual usage, not just entry time
//Most recently used pages stay in memory longer
//More complex implementation than FIFO
