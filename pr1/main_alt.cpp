#include <string>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Alloy {
    string id;
    float flex;
    float cond;
    bool operator==(const Alloy& other) const {
        return id == other.id;
    }
    void print() {
        std::cout << id << ' ' << flex << ' ' << cond << std::endl;
    }
};

void readAlloys(vector<Alloy> *alloys, int alloy_num) {    
    float max_flex = 0, max_cond = 0;
    for (int i = 0; i < alloy_num; i++) {
        Alloy alloy;
        std::cin >> alloy.id >> alloy.flex >> alloy.cond;
        bool dom = false;

        if (alloy.flex > max_flex) {
            max_flex = alloy.flex;
            dom = true;
        }
        if (alloy.cond > max_cond) {
            max_cond = alloy.cond;
            dom = true;
        }
        // Check all dominant elements
        for (auto it = alloys->begin(); it != alloys->end();) {
            // If better in both f and c axis, delete from list
            if (alloy.flex > it->flex && alloy.cond > it->cond) {
                alloys->erase(it);
            } else {
                it++;
            }
        }
        // Add to list if dominant
        if (dom) {
            alloys->push_back(alloy);
        }
    }
}

int main() {
    int alloy_num;
    std::cin >> alloy_num;
    std::vector<Alloy> dom_alloys;
    readAlloys(&dom_alloys, alloy_num);
    // Sort by id
    std::sort(dom_alloys.begin(), dom_alloys.end(),
        [](const Alloy& a, const Alloy& b) {
            return a.id < b.id; // compare ids
        }
    );
    std::for_each(dom_alloys.begin(), dom_alloys.end(), [](Alloy a) { a.print(); });
    return 0;
}