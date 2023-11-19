#include <iostream>
#include <deque>
#include <unordered_set>
#include <algorithm>

using namespace std;

int main()
{
    int frame_size = 4;
    int arr[] = {7,0,1,2,0,3,0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};

    deque<int> q(frame_size);
    unordered_set<int> pageSet; // To keep track of pages currently in the queue
    int count = 0;
    int page_faults = 0;
    int page_hits = 0;
    deque<int>::iterator itr;
    q.clear();

    for (int i : arr)
    {

        // Insert it into set if not present
        // already which represents page fault
        itr = find(q.begin(), q.end(), i);
        if (!(itr != q.end()))
        {

            ++page_faults;

            // Check if the set can hold equal pages
            if (q.size() == frame_size)
            {
                // Remove the least recently used page from set
                pageSet.erase(q.front());
                q.pop_front();

                q.push_back(i);
                pageSet.insert(i);
            }
            else
            {
                q.push_back(i);
                pageSet.insert(i);
            }
        }
        else
        {
            // Remove the indexes page
            q.erase(itr);

            // insert the current page
            q.push_back(i);
            pageSet.erase(i);
            pageSet.insert(i);

            // It's a hit
            ++page_hits;
        }
    }

    cout << "Page Faults: " << page_faults << endl;
    cout << "Page Hits: " << page_hits << endl;
}
