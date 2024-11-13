#include <bits/stdc++.h>
using namespace std;

// Predict the page to replace by finding the page that will not be used for the longest time
int predictPageToReplace(const vector<int>& pages, const vector<int>& frame, int currentIndex) {
    int maxIndex = -1, pageToReplaceIndex = -1;
    
    // Check each page in the frame to see when it will be used next
    for (int i = 0; i < frame.size(); i++) {
        int j;
        for (j = currentIndex; j < pages.size(); j++) {
            if (frame[i] == pages[j]) {
                if (j > maxIndex) {
                    maxIndex = j;
                    pageToReplaceIndex = i;
                }
                break;
            }
        }
        
        // If a page is not used again, it’s a good candidate to replace
        if (j == pages.size()) return i;
    }
    return pageToReplaceIndex;
}

void optimalPageReplacement(const vector<int>& pages, int numFrames) {
    vector<int> frame;
    int pageFaults = 0;
    vector<int> pageFaultsArray(pages.size(), 0);
    vector<int> pageHitsArray(pages.size(), 0);

    for (int i = 0; i < pages.size(); i++) {
        if (find(frame.begin(), frame.end(), pages[i]) != frame.end()) {
            pageHitsArray[i] = 1;  // Page hit
            cout << "Page " << pages[i] << " hit. Frame: ";
        } else {
            pageFaults++;
            pageFaultsArray[i] = 1;  // Page fault

            if (frame.size() < numFrames) {
                frame.push_back(pages[i]);
            } else {
                int replaceIndex = predictPageToReplace(pages, frame, i + 1);
                frame[replaceIndex] = pages[i];
            }
            cout << "Page " << pages[i] << " fault. Frame: ";
        }
        
        for (int page : frame) cout << page << " ";
        cout << endl;
    }

    // Display the results
    cout << "\nPage Faults Array: ";
    for (int fault : pageFaultsArray) cout << fault << " ";
    cout << "\nPage Hits Array: ";
    for (int hit : pageHitsArray) cout << hit << " ";
    cout << "\nTotal Hits = " << pages.size() - pageFaults;
    cout << "\nTotal Faults = " << pageFaults << endl;
}

int main() {
    int numPages, numFrames;
    cout << "Enter the number of pages: ";
    cin >> numPages;
    vector<int> pages(numPages);

    cout << "Enter the page numbers:\n";
    for (int i = 0; i < numPages; i++) cin >> pages[i];

    cout << "Enter the number of frames: ";
    cin >> numFrames;

    optimalPageReplacement(pages, numFrames);
    return 0;
}

//This code implements the Optimal Page Replacement Algorithm (also known as Bélády's algorithm or the clairvoyant algorithm) for page replacement in operating systems. 

//This code implements the Optimal Page Replacement Algorithm, which is a theoretical page replacement algorithm used in operating systems for page fault handling. 

//This function decides which page to remove when memory is full:

//It looks into the future sequence of page requests
//Finds the page that won't be used for the longest time
//That page is chosen for replacement
