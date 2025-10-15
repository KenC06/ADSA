// main.cpp
// ADSA A3 — Hash table with linear probing (26 slots, last-char hash)

#include <bits/stdc++.h>
using namespace std;

struct Slot {
    // 0 = never used, 1 = tombstone, 2 = occupied
    int status = 0;
    string key;
};

static inline int hidx(const string& s) {
    // hash is the last character (0 for 'a' ... 25 for 'z')
    return static_cast<int>(s.back() - 'a');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // read the single input line of moves
    string line;
    if (!getline(cin, line)) line = "";
    stringstream ss(line);
    vector<string> moves;
    for (string tok; ss >> tok; ) moves.push_back(tok);

    // table with 26 slots
    array<Slot, 26> table;

    for (const string& move : moves) {
        if (move.empty()) continue;
        char op = move[0];            // 'A' or 'D'
        string key = move.substr(1);  // lower-case word, len <= 10

        int start = hidx(key);
        int pos = start;

        if (op == 'A') {
            // 1) search to ensure key doesn't already exist
            bool exists = false;
            while (table[pos].status != 0) { // stop at first "never used"
                if (table[pos].status == 2 && table[pos].key == key) {
                    exists = true;
                    break;
                }
                pos = (pos + 1) % 26;
                if (pos == start) break; // full loop safety (shouldn't happen under n<=26)
            }
            if (exists) continue;

            // 2) insert at first slot that is not occupied (never-used or tombstone)
            pos = start;
            while (table[pos].status == 2) {
                pos = (pos + 1) % 26;
            }
            table[pos].status = 2;
            table[pos].key = key;
        }
        else if (op == 'D') {
            // locate and tombstone if found
            pos = start;
            while (table[pos].status != 0) { // stop at first "never used" (definitely not present)
                if (table[pos].status == 2 && table[pos].key == key) {
                    table[pos].status = 1;   // tombstone
                    table[pos].key.clear();
                    break;
                }
                pos = (pos + 1) % 26;
                if (pos == start) break; // full loop safety
            }
        }
        // per spec: inputs are valid; ignore anything else
    }

    // output occupied keys in slot order a..z, separated by a single space
    bool first = true;
    for (const auto& s : table) {
        if (s.status == 2) {
            if (!first) cout << ' ';
            cout << s.key;
            first = false;
        }
    }
    cout << '\n';
    return 0;
}
