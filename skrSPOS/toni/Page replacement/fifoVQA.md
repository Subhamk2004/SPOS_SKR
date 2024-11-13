### **Code Explanation:**

#### **Objective:**
This code simulates the **FIFO (First-In-First-Out)** page replacement algorithm. It simulates how a page fault occurs when a page is accessed but not found in memory (frames), and how the oldest page in memory is replaced when a new page needs to be loaded into memory.

#### **Key Concepts:**
1. **Page Fault:** When the requested page is not present in memory (frames), and it needs to be loaded into memory.
2. **Page Hit:** When the requested page is already present in memory (no replacement required).
3. **FIFO (First-In-First-Out):** The page that has been in memory the longest is replaced when a new page needs to be loaded.

---

### **Code Walkthrough:**

#### 1. **Function `fifoPage`**:
This function implements the FIFO page replacement algorithm.

##### **Parameters:**
- `pg`: A vector representing the sequence of page accesses.
- `pn`: Total number of pages (length of `pg`).
- `fn`: The number of frames available in memory.

##### **Variables:**
- `fr`: A vector representing the current pages in memory (the frame).
- `fifoQueue`: A queue that stores the page numbers in the order they were added to memory, used to identify the oldest page for replacement.
- `pageFaults`: Counter for the number of page faults.
- `pageFaultsArray`: A vector to store `1` for page faults and `0` for page hits.
- `pageHitsArray`: A vector to store `1` for page hits and `0` for page faults.

#### 2. **Page Access Logic:**
- **For each page in the access sequence (`pg`):**
  - If the page is **not in `fr[]`**, it results in a **page fault**:
    - If there is space in memory (i.e., `fr[]` size < `fn`), the page is added to the memory.
    - If memory is full, the oldest page (first page in `fifoQueue`) is replaced with the new page.
  - If the page is **already in `fr[]`**, it is a **page hit**:
    - Update the order of the pages in `fifoQueue` to reflect the most recently used page.

#### 3. **FIFO Replacement Logic:**
- When the memory is full (i.e., `fr[]` size equals `fn`), the oldest page (the one at the front of `fifoQueue`) is replaced by the new page.
- The page that is being replaced is removed from `fr[]`, and the new page is added.

#### 4. **Display Results:**
- After processing each page access, the program displays the current contents of the memory frames (`fr[]`).
- At the end, it displays the **Page Faults Array** and **Page Hits Array**.

#### 5. **Main Function:**
- Takes input for the number of pages and the page numbers.
- Takes input for the frame size (`fn`).
- Calls the `fifoPage` function to simulate page access and handle page faults and hits.

---

### **Code Breakdown:**

```cpp
void fifoPage(const vector<int>& pg, int pn, int fn) {
    vector<int> fr;  // Frame (stores pages in memory)
    queue<int> fifoQueue;  // Keeps track of the order of pages for FIFO replacement
    int pageFaults = 0;

    vector<int> pageFaultsArray(pn, 0);  // To mark page faults
    vector<int> pageHitsArray(pn, 0);    // To mark page hits

    for (int i = 0; i < pn; i++) {
        int currentPage = pg[i];
        
        // Check if the page is not in the frame (page fault)
        if (find(fr.begin(), fr.end(), currentPage) == fr.end()) {
            pageFaults++;
            pageFaultsArray[i] = 1;  // Mark as page fault

            if (fr.size() < fn) {
                fr.push_back(currentPage);  // Add the page to memory if space is available
                fifoQueue.push(currentPage);
            } else {
                int replacedPage = fifoQueue.front();  // Replace the oldest page
                fifoQueue.pop();
                
                // Find and replace the oldest page in `fr[]`
                for(int j = 0; j < fr.size(); j++){
                    if(fr[j] == replacedPage) {
                        fr[j] = currentPage;  // Replace the oldest page
                    }
                }
                fifoQueue.push(currentPage);
            }
        } else {
            pageHitsArray[i] = 1;  // Mark as page hit
        }

        // Display current frame contents after accessing the page
        cout << "Page " << currentPage << " is in the frame. Frame Contents: ";
        for (int page : fr) {
            cout << page << " ";
        }
        cout << endl;
    }

    // Display the final page hits and page faults arrays
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
```

- **Inside the loop:** The page access sequence is processed by checking if the current page is in memory (`fr[]`). If it's not, a page fault occurs, and either the page is added to memory or an old page is replaced based on the FIFO policy.
  
- **FIFO Replacement:** The oldest page is identified by checking the page at the front of the `fifoQueue` and replacing it in memory (`fr[]`).

---

### **Example Walkthrough:**

#### **Input:**
- Pages: `1 2 3 4 1 2 5`
- Frame Size: `3`

#### **Step-by-Step Process:**

1. **Page 1:**  
   - Frame: `[1]` (Fault, added page 1)
2. **Page 2:**  
   - Frame: `[1, 2]` (Fault, added page 2)
3. **Page 3:**  
   - Frame: `[1, 2, 3]` (Fault, added page 3)
4. **Page 4:**  
   - Frame: `[4, 2, 3]` (Fault, replaced oldest page 1 with page 4)
5. **Page 1:**  
   - Frame: `[4, 2, 1]` (Fault, replaced oldest page 3 with page 1)
6. **Page 2:**  
   - Frame: `[4, 2, 1]` (Hit, no replacement needed)
7. **Page 5:**  
   - Frame: `[5, 2, 1]` (Fault, replaced oldest page 4 with page 5)

#### **Output:**
- **Page Faults Array:** `1 1 1 1 0 0 1`
- **Page Hits Array:** `0 0 0 0 1 1 0`
- **Final Frame Contents:** `[5 2 1]`

---

### **Viva Questions and Answers:**

1. **What is the FIFO page replacement algorithm?**
   - FIFO replaces the page that has been in memory the longest (i.e., the first page in memory).

2. **What is a page fault in the FIFO algorithm?**
   - A page fault occurs when the requested page is not found in the frames, and it must be loaded into memory.

3. **What happens when the frame is full in FIFO?**
   - The oldest page (the one that was loaded first) is replaced with the new page.

4. **How does the FIFO algorithm differ from LRU?**
   - FIFO replaces the oldest page regardless of how recently it was used, whereas LRU replaces the least recently used page.

5. **Why is the queue used in the FIFO algorithm?**
   - The queue helps track the order of page accesses, so the oldest page can be easily identified and replaced when necessary.

---

### **Summary:**
This C++ program simulates the **FIFO page replacement** algorithm, processing a sequence of page accesses and managing the memory frames accordingly. The program tracks page hits and page faults and displays the state of memory after each access. It effectively demonstrates the FIFO policy where the oldest page is replaced when new pages are needed in full memory.
