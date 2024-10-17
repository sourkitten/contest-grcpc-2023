#include <string>
#include <set>
#include <iostream>
using namespace std;

struct Alloy {
    string id;
    float flex;
    float cond;

    // Printing function to display the alloy's properties
    void print() const {
        if (flex != 0) {
            std::cout << id << ' ' << flex << ' ' << cond << std::endl;
        }
    }
};

// Custom comparator for the set
struct AlloyComparator {
    bool operator()(const Alloy& a, const Alloy& b) const {
        // Finally, compare by id (for uniqueness in the set)
        return a.id < b.id;
    }
};

// Function to read and process alloys
void readAlloys(set<Alloy, AlloyComparator>& alloys, int alloy_num) {
    float max_flex = 0, max_cond = 0;

    for (int i = 0; i < alloy_num; i++) {
        Alloy alloy;
        std::cin >> alloy.id >> alloy.flex >> alloy.cond;
        bool is_dominant = false;

        // Check if this alloy is dominant in flexibility or conductivity
        if (alloy.flex > max_flex) {
            max_flex = alloy.flex;
            is_dominant = true;
        }
        if (alloy.cond > max_cond) {
            max_cond = alloy.cond;
            is_dominant = true;
        }

        // Remove any alloys that this one dominates
        for (auto it = alloys.begin(); it != alloys.end();) {
            if (alloy.flex > it->flex && alloy.cond > it->cond) {
                it = alloys.erase(it);  // erase and get the next iterator
            } else {
                ++it;
            }
        }

        // Add to set if dominant
        if (is_dominant) {
            alloys.insert(alloy);  // Insert the new dominant alloy
        }
    }
}

int main() {
    int alloy_num;
    std::cin >> alloy_num;

    // Define a set with the custom comparator
    std::set<Alloy, AlloyComparator> dom_alloys;

    // Read and process alloys
    readAlloys(dom_alloys, alloy_num);

    // Since the set already sorts by flex and cond, we just need to print
    for (const Alloy& a : dom_alloys) {
        a.print();
    }

    return 0;
}
