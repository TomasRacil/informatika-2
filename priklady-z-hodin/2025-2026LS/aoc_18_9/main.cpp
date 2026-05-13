#include <iostream>
#include <vector>

using namespace std;

struct Node {
    long long value;
    Node* prev;
    Node* next;

    Node(long long val) : value(val), prev(nullptr), next(nullptr) {}
};

Node* insertAfter(Node* target, long long value) {
    Node* neighbor_right = target->next;
    Node* newNode = new Node(value);
    newNode->prev = target;
    newNode->next = neighbor_right;
    target->next = newNode;
    neighbor_right->prev = newNode;
    return newNode;
}

Node* removeNode(Node* target) {
    Node* before = target->prev;
    Node* after = target->next;
    before->next = after;
    after->prev = before;
    delete target;
    return after;
}

long long solve(int players, int last_marble) {
    vector<long long> scores(players, 0);

    Node* current = new Node(0);
    current->next = current;
    current->prev = current;

    for (int m = 1; m <= last_marble; ++m) {
        if (m % 23 == 0) {
            int player_idx = (m - 1) % players;
            
            for (int i = 0; i < 7; ++i) {
                current = current->prev;
            }

            scores[player_idx] += m + current->value;

            current = removeNode(current);
        } else {
            current = insertAfter(current->next, m);
        }
    }

    long long max_s = 0;
    for (long long s : scores) {
        if (s > max_s) max_s = s;
    }

    return max_s;
}

int main() {
    cout << "Vysledky testovacich scenaru:" << endl;
    cout << "9 hracu, 25 kulicek: " << solve(9, 25) << " (Cil: 32)" << endl;
    cout << "10 hracu, 1618 kulicek: " << solve(10, 1618) << " (Cil: 8317)" << endl;
    cout << "13 hracu, 7999 kulicek: " << solve(13, 7999) << " (Cil: 146373)" << endl;
    cout << "17 hracu, 1104 kulicek: " << solve(17, 1104) << " (Cil: 2764)" << endl;
    cout << "21 hracu, 6111 kulicek: " << solve(21, 6111) << " (Cil: 54718)" << endl;
    cout << "30 hracu, 5807 kulicek: " << solve(30, 5807) << " (Cil: 37305)" << endl;
    cout << "458 hracu, 72019 kulicek: " << solve(458, 72019) << " (Cil: 404502)" << endl;
    cout << "458 hracu, 7201900 kulicek: " << solve(458, 7201900) << " (Cil: 3243916887)" << endl;
    return 0;
}