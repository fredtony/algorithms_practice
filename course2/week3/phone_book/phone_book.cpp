#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::sqrt;

bool isPrime(unsigned int n) {
    unsigned int i, root;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    root = (unsigned int)sqrt(n);
    for (i = 5; i <= root; i += 6) {
        if (n % i == 0)
           return false;
    }
    for (i = 7; i <= root; i += 6) {
        if (n % i == 0)
           return false;
    }

    return true;
}

unsigned int find_prime(unsigned int n){
    int i = n + 1;
    while(true) {
        if(isPrime(i++))
            break;
    }
    return i;
}

unsigned int hash(unsigned int x, unsigned int mod_val) {
    // x = ((x >> 16) ^ x) * 0x45d9f3b;
    // x = ((x >> 16) ^ x) * 0x45d9f3b;
    // x = (x >> 16) ^ x;
    x = (x * 98421 + 157) % find_prime(mod_val+10000);
    return x % mod_val;
}

struct Node {
    int num;
    string name;
    Node * next_node;
    Node(int num, string name) : num(num), name(name), next_node(nullptr) {}
};

struct Query {
    string type, name;
    int number;
};

vector<Query> read_queries(unsigned int & num_adds) {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add") {
            num_adds++;
            cin >> queries[i].number >> queries[i].name;
        }
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        cout << result[i] << "\n";
}

vector<string> process_queries(const vector<Query>& queries, unsigned int & num_adds) {
    vector<string> result;
    num_adds *= 2;
    vector<Node *> contacts(num_adds, nullptr);
    Node * node;
    for (size_t i = 0; i < queries.size(); ++i) {
        if (queries[i].type == "find") {
            // cout << "find\n";
            node = contacts[hash(queries[i].number, num_adds)];
            while (true) {
                if (node == nullptr) {
                    result.push_back("not found");
                    break;
                }
                else if (node->num == queries[i].number) {
                    result.push_back(node->name);
                    break;
                }
                node = node->next_node;
            }
        }
        else if (queries[i].type == "add") {
            // cout << "add\n";
            unsigned int hash_val = hash(queries[i].number, num_adds);
            node = contacts[hash_val];
            if (node == nullptr)
                contacts[hash_val] = new Node(queries[i].number, queries[i].name);
            else {
                while (true) {
                    if (node->num == queries[i].number) {
                        node->name = queries[i].name;
                        break;
                    }
                    if (node->next_node == nullptr) {
                        node->next_node = new Node(queries[i].number, queries[i].name);
                        break;
                    }
                    node = node->next_node;
                }
            }
        }
        else {
            // cout << "delete\n";
            unsigned int hash_val = hash(queries[i].number, num_adds);
            node = contacts[hash_val];
            if (node == nullptr) {}
            else if (node->num == queries[i].number) {
                contacts[hash_val] = node->next_node;
                delete node;
            }
            else {
                while (node->next_node != nullptr) {
                    if (node->next_node->num == queries[i].number) {
                        Node * tmp_node = node->next_node;
                        node->next_node = node->next_node->next_node;
                        delete tmp_node;
                        break;
                    }
                    node = node->next_node;
                }
            }
        }
    }
    return result;
}

int main() {
    unsigned int num_adds = 0;
    write_responses(process_queries(read_queries(num_adds), num_adds));
    return 0;
}
