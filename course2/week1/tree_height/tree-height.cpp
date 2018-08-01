#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using namespace std;

class Node;

class Node {
public:
    int key;
    Node *parent;
    vector<Node *> children;

    Node() {
        this->parent = NULL;
    }

    void setParent(Node *theParent) {
        parent = theParent;
        parent->children.push_back(this);
    }
};


int main_with_large_stack_space() {
    ios_base::sync_with_stdio(0);
    int n, parent_index, root_index, maxHeight = 1, current, new_key;
    cin >> n;

    vector<Node> nodes(n);
    // nodes.resize(n);
    for (int child_index=0; child_index<n; child_index++) {
        cin >> parent_index;
        if (parent_index >= 0)
            nodes[child_index].setParent(&nodes[parent_index]);
        else
            root_index = child_index;
        nodes[child_index].key = child_index;
    }

    queue<int> node_queue;
    vector<int> heights(nodes.size());
    heights[root_index] = 1;
    for (int i=0; i<(int)nodes[root_index].children.size(); i++) {
        new_key = nodes[root_index].children[i]->key;
        heights[new_key] = heights[root_index] + 1;
        maxHeight = max(maxHeight, heights[new_key]);
        node_queue.push(new_key);
    }
    while (!node_queue.empty()) {
        current = node_queue.front();
        node_queue.pop();
        for (int i=0; i<(int)nodes[current].children.size(); i++) {
            new_key = nodes[current].children[i]->key;
            heights[new_key] = heights[current] + 1;
            maxHeight = max(maxHeight, heights[new_key]);
            node_queue.push(new_key);
        }
    }

    cout << maxHeight << endl;
    return 0;
}

int main (int argc, char **argv) {
#if defined(__unix__) || defined(__APPLE__)
    // Allow larger stack space
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0) {
        if (rl.rlim_cur < kStackSize) {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0) {
                cerr << "setrlimit returned result = " << result << endl;
            }
        }
    }
#endif
    return main_with_large_stack_space();
}
